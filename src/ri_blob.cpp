/*
Copyright 2016 Open Robot Club

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <openri.h>

#include <iostream>
#include <cmath>


using namespace std;


RI_API int RiBlob_New(RiBlob_t* riBlob) {
    riBlob->grayMin   = 255;	//white
    riBlob->grayMax   = 255;
    riBlob->widthMax      = INT_MAX;
    riBlob->widthMin      = 0;
    riBlob->heightMax      = INT_MAX;
    riBlob->heightMin      = 0;
    riBlob->areaMax      = INT_MAX;
    riBlob->areaMin      = 0;

    riBlob->isGrayAvgEnabled   = 0;
    riBlob->isCenterXyEnabled  = 0;
	return 1;
}

RI_API int RiBlob_Free(RiBlob_t* riBlob)
{
    free(riBlob);
	return 1;
}

RI_API vector<RiBlobObj_t> getRiBlobObjs(RiBlob_t* riBlob)
{
	return riBlob->blobObjs;
}

RI_API unsigned short* getTagMap(RiBlob_t* riBlob)
{
    return riBlob->tagMap;
}

RI_API int setThresholds(RiBlob_t* riBlob, unsigned char grayMin, unsigned char grayMax, int widthMin, int widthMax, int heightMin, int heightMax, int areaMin, int areaMax)
{
    riBlob->grayMin = grayMin;
    riBlob->grayMax = grayMax;
    riBlob->widthMax = widthMax;
    riBlob->widthMin = widthMin;
    riBlob->heightMax = heightMax;
    riBlob->heightMin = heightMin;
    riBlob->areaMax = areaMax;
    riBlob->areaMin = areaMin;

    return 1;
}

RI_API int RiBlob_EnableGrayAvg(RiBlob_t* riBlob, int isGrayAvgEnabled)
{
    riBlob->isGrayAvgEnabled = isGrayAvgEnabled;

    return 1;
}

RI_API int RiBlob_EnableCenterXy(RiBlob_t* riBlob, int isCenterXyEnabled)
{
    riBlob->isCenterXyEnabled = isCenterXyEnabled;

    return 1;
}

RI_API int findBlob(RiBlob_t* riBlob, Mat *matSrc, Mat *matDst)
{
    if (matSrc->cols == 0) return 0;
    if (matSrc->rows == 0) return 0;

    riBlob->width = matSrc->cols;
    riBlob->height = matSrc->rows;

    vector<RiBlobPoint_t> blobPoints;

	if (riBlob->tagMap != NULL)
    {
        free(riBlob->tagMap);
    }
    riBlob->tagMap = (unsigned short*)calloc( riBlob->width * riBlob->height, sizeof(unsigned short)); //calloc: set to 0.


    int x, y, i, j;
    int count = 0;
    uchar* ptr, *ptr_ym, *ptr_yp, *ptr_y;
    for(j = 0; j < riBlob->height; j ++)
    {
        ptr = matSrc->ptr<uchar>(j);
        for(i = 0; i < riBlob->width; i ++)
        {
            //if not tagged && is white
            if (riBlob->tagMap[i + j * riBlob->width] == 0 && ptr[i] >= riBlob->grayMin && ptr[i] <= riBlob->grayMax)
            {
                count++;
                riBlob->tagMap[i + j * riBlob->width] = count;

                //create a new blob, add into array.
                RiBlobPoint_t  blobPoint;
                blobPoint.x = i;
                blobPoint.y = j;

                //push into queue
                blobPoints.push_back(blobPoint);	

                while(!blobPoints.empty())
                {
                    // Get the last blob and delete it.
                    blobPoint = blobPoints.back();	
                    blobPoints.pop_back();

                    x = blobPoint.x;
                    y = blobPoint.y; 
                    ptr_y = matSrc->ptr<uchar>(y);


                    
                    // Check around that blob. 
                    // Up
                    if ((y - 1) >= 0)
                    {
                        ptr_ym = matSrc->ptr<uchar>(y - 1);
                        if (riBlob->tagMap[riBlob->width * (y - 1) + (x)] == 0 && ptr_ym[x] >= riBlob->grayMin && ptr_ym[x] <= riBlob->grayMax)
                        {
                            riBlob->tagMap[riBlob->width * (y - 1) + (x)] = count;
                            blobPoint.x = (x);
                            blobPoint.y = (y - 1);
                            blobPoints.push_back(blobPoint);
                        }
                    }

                    // Right
                    if ((x + 1) < riBlob->width)
                    {
                        if (riBlob->tagMap[riBlob->width * (y) + (x + 1)] == 0 && ptr_y[x + 1] >= riBlob->grayMin && ptr_y[x + 1] <= riBlob->grayMax)
                        {
                            riBlob->tagMap[riBlob->width * (y) + (x + 1)] = count;
                            blobPoint.x = (x + 1);
                            blobPoint.y = (y);
                            blobPoints.push_back(blobPoint);
                        }
                    }

                    // Down
                    if ((y + 1) < riBlob->height)
                    {
                        ptr_yp = matSrc->ptr<uchar>(y + 1);
                        if (riBlob->tagMap[riBlob->width * (y + 1) + (x)] == 0 && ptr_yp[x] >= riBlob->grayMin && ptr_yp[x] <= riBlob->grayMax)
                        {
                            riBlob->tagMap[riBlob->width * (y + 1) + (x)] = count;
                            blobPoint.x = (x);
                            blobPoint.y = (y + 1);
                            blobPoints.push_back(blobPoint);
                        }
                    }

                    // Left
                    if ((x - 1) >= 0)
                    {
                        if (riBlob->tagMap[riBlob->width * (y) + (x - 1)] == 0 && ptr_y[x - 1] >= riBlob->grayMin && ptr_y[x - 1] <= riBlob->grayMax)
                        {
                            riBlob->tagMap[riBlob->width * (y) + (x - 1)] = count;
                            blobPoint.x = (x - 1);
                            blobPoint.y = (y);
                            blobPoints.push_back(blobPoint);
                        }
					}


					// Left Up
					if ((x - 1) >= 0 && (y - 1) >= 0 ) {
						ptr_ym = matSrc->ptr<uchar>(y - 1);

						if (riBlob->tagMap[riBlob->width * (y - 1) + (x - 1)] == 0 && ptr_ym[x - 1] >= riBlob->grayMin && ptr_ym[x - 1] <= riBlob->grayMax)
						{
							riBlob->tagMap[riBlob->width * (y - 1) + (x - 1)] = count;
							blobPoint.x = (x - 1);
							blobPoint.y = (y - 1);
							blobPoints.push_back(blobPoint);
						}

					}
					//Left Down
					if ((x - 1) >= 0 && (y + 1) < riBlob->height) {
						ptr_yp = matSrc->ptr<uchar>(y + 1);
						if (riBlob->tagMap[riBlob->width * (y + 1) + (x - 1)] == 0 && ptr_yp[x - 1] >= riBlob->grayMin && ptr_yp[x - 1] <= riBlob->grayMax)
						{
							riBlob->tagMap[riBlob->width * (y + 1) + (x - 1)] = count;
							blobPoint.x = (x - 1);
							blobPoint.y = (y + 1);
							blobPoints.push_back(blobPoint);
						}

					}

					//Right Up
					if ((x + 1) < riBlob->width && (y - 1) >= 0) {
						ptr_ym = matSrc->ptr<uchar>(y - 1);
						if (riBlob->tagMap[riBlob->width * (y - 1) + (x + 1)] == 0 && ptr_ym[x + 1] >= riBlob->grayMin && ptr_ym[x + 1] <= riBlob->grayMax)
						{
							riBlob->tagMap[riBlob->width * (y - 1) + (x + 1)] = count;
							blobPoint.x = (x + 1);
							blobPoint.y = (y - 1);
							blobPoints.push_back(blobPoint);
						}
					}

					//Right Down
					if ((x + 1) < riBlob->width &&  (y + 1) < riBlob->height) {
						ptr_yp = matSrc->ptr<uchar>(y + 1);
						if (riBlob->tagMap[riBlob->width * (y + 1) + (x + 1)] == 0 && ptr_yp[x + 1] >= riBlob->grayMin && ptr_yp[x + 1] <= riBlob->grayMax)
						{
							riBlob->tagMap[riBlob->width * (y + 1) + (x + 1)] = count;
							blobPoint.x = (x + 1);
							blobPoint.y = (y + 1);
							blobPoints.push_back(blobPoint);
						}
					}



                }//end while
            }//end if
        }//end for i
    }  //end for j


    riBlob->blobObjs.clear();			//clear previous stuff.
    RiBlobObj_t obj;

    for(x = 1; x <= count; x ++) {
        obj.tag = x;
        obj.area = 0;
        obj.grayTotal = 0;
        obj.xCenterTotal = 0;
        obj.yCenterTotal = 0;
        obj.xMax = obj.yMax = 0;
        obj.xMin = obj.yMin = INT_MAX;
        obj.examined = 0;

		riBlob->blobObjs.push_back(obj);
    }

    // 根據tagMap, 計算每個BlobObj的 min max
    int tag;
    for(y = 0; y < riBlob->height; y++)
    {
        for(x = 0; x < riBlob->width; x++)
        {
            tag = riBlob->tagMap[x + y * riBlob->width];
            if (tag == 0)	continue;

            //RiBlobObj_t &ptrObj = riBlob->blobObjs[tag - 1];

            riBlob->blobObjs[tag - 1].area ++;
            if (riBlob->blobObjs[tag - 1].xMax < x)	riBlob->blobObjs[tag - 1].xMax = x;
            if (riBlob->blobObjs[tag - 1].xMin > x)	riBlob->blobObjs[tag - 1].xMin = x;
            if (riBlob->blobObjs[tag - 1].yMin > y)	riBlob->blobObjs[tag - 1].yMin = y;
            if (riBlob->blobObjs[tag - 1].yMax < y)	riBlob->blobObjs[tag - 1].yMax = y;

            if (riBlob->isGrayAvgEnabled == 1)
            {
                riBlob->blobObjs[tag - 1].grayTotal += matSrc->at<uchar>(y,x);
            }

            if (riBlob->isCenterXyEnabled == 1)
            {
                riBlob->blobObjs[tag - 1].xCenterTotal += x;
                riBlob->blobObjs[tag - 1].yCenterTotal += y;
            }
        }
    } //end for

    filterBlobs(riBlob, matSrc);   

    return count;
}

RI_API int countAndPrint(RiBlob_t* riBlob, Mat *matSrc, Mat *matDst)
{
    int count = 0;
    matDst = matSrc;
    for(int i = 0; i < riBlob->blobObjs.size(); i++)
    {
        Point org(riBlob->blobObjs[i].xCenter, riBlob->blobObjs[i].yCenter);
        // char* tmp = new char [10];
        // sprintf_s(tmp, "(%d, %d)", blobObjs[i].xCenter, blobObjs[i].yCenter);
        // putText(matDst, tmp, org, FONT_HERSHEY_PLAIN, 1, Scalar(255, 100, 0), 1, 1);
        count++;
    }

    return count;
}

RI_API int sortTagByXmin( vector<RiBlobObj_t> *inputBlobs, int rowOffset)
{
    vector<RiBlobObj_t> sortingArray;
    if (inputBlobs->size() < 1)
    {
        return -1;
    }
	sortingArray.push_back(inputBlobs->at(0));

    for(int i = 1; i < inputBlobs->size(); i++)
    {
        bool inserted = false;
        for(int j = 0; j < sortingArray.size(); j++)
        {
			if (inputBlobs->at(i).yCenter > sortingArray[j].yCenter + rowOffset)
                continue;
            if (inputBlobs->at(i).xMin < sortingArray[j].xMin)
            {
                sortingArray.insert(sortingArray.begin()+j, inputBlobs->at(i));
                sortingArray[j].tag = j + 1;
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            sortingArray.push_back(inputBlobs->at(i));
        }
    }
    for(int i = 0; i < sortingArray.size(); i++)
    {
        sortingArray[i].tag = i + 1;
    }
    *inputBlobs = sortingArray;

    return 1;
}

RI_API int sortTagByXmin( vector<RiBlobObj_t> *inputBlobs)
{
    vector<RiBlobObj_t> *sortingArray;
    if (inputBlobs->size() < 1)
    {
        return -1;
    }
	sortingArray = (vector<RiBlobObj_t>*)malloc(sizeof(RiBlobObj_t) * inputBlobs->size());
    sortingArray->push_back(inputBlobs->at(0));

    for(int i = 1; i < inputBlobs->size(); i++)
    {
        bool inserted = false;
        for(int j = 0; j < sortingArray->size(); j++)
        {
			if (inputBlobs->at(i).xMin < sortingArray->at(j).xMin)
            {
                sortingArray->insert(sortingArray->begin() + j, inputBlobs->at(i));
                sortingArray->at(j).tag = j + 1;
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            sortingArray->push_back(inputBlobs->at(i));
        }
    }
    for(int i = 0; i < sortingArray->size(); i++)
    {
        sortingArray->at(i).tag = i + 1;
	}
	if(!inputBlobs) {
		free(inputBlobs);
	}
	inputBlobs = sortingArray;

    return 1;
}

RI_API int sortTagByArea( vector<RiBlobObj_t> *inputBlobs)
{
    vector<RiBlobObj_t> *sortingArray;
    if (inputBlobs->size() < 1)
    {
        return -1;
    }

	sortingArray = (vector<RiBlobObj_t>*)malloc(sizeof(RiBlobObj_t) * inputBlobs->size());
    sortingArray->push_back(inputBlobs->at(0));

    for(int i = 1; i < inputBlobs->size(); i++)
    {
        bool inserted = false;
        for(int j = 0; j < sortingArray->size(); j++)
        {
            if (inputBlobs->at(i).area > sortingArray->at(j).area)
            {
                sortingArray->insert(sortingArray->begin() + j, inputBlobs->at(i));
                sortingArray->at(j).tag = j + 1;
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            sortingArray->push_back(inputBlobs->at(i));
        }
    }
    for(int i = 0; i < sortingArray->size(); i++)
    {
        sortingArray->at(i).tag = i + 1;
    }
	if(!inputBlobs) {
		free(inputBlobs);
	}
    inputBlobs = sortingArray;

    return 1;
}

RI_API int filterBlobs(RiBlob_t* riBlob, Mat *matSrc)
{
    int count = (int)riBlob->blobObjs.size();

    for(int x = count - 1; x >= 0; x--) 
    {
        //RiBlobObj_t &ptrObj = riBlob->blobObjs[x];

		riBlob->blobObjs[x].height = riBlob->blobObjs[x].yMax - riBlob->blobObjs[x].yMin + 1;
		riBlob->blobObjs[x].width  = riBlob->blobObjs[x].xMax - riBlob->blobObjs[x].xMin + 1;

        if (riBlob->blobObjs[x].width < riBlob->widthMin || riBlob->blobObjs[x].width > riBlob->widthMax)
        {
            riBlob->blobObjs.erase(riBlob->blobObjs.begin() + x);
            continue;
        }   

        if (riBlob->blobObjs[x].height < riBlob->heightMin || riBlob->blobObjs[x].height > riBlob->heightMax)
        {
            riBlob->blobObjs.erase(riBlob->blobObjs.begin() + x);
            continue;   
        }

        if (riBlob->blobObjs[x].area < riBlob->areaMin || riBlob->blobObjs[x].area > riBlob->areaMax)
        {
			riBlob->blobObjs.erase(riBlob->blobObjs.begin() + x);
            continue;   
        }

        if (riBlob->isGrayAvgEnabled == 1)
        {
            riBlob->blobObjs[x].grayAvg = riBlob->blobObjs[x].grayTotal / riBlob->blobObjs[x].area;
        }

        if (riBlob->isCenterXyEnabled == 1)
        {
            riBlob->blobObjs[x].xCenter = riBlob->blobObjs[x].xCenterTotal / riBlob->blobObjs[x].area;
            riBlob->blobObjs[x].yCenter = riBlob->blobObjs[x].yCenterTotal / riBlob->blobObjs[x].area;
        }
    }

    return 1;
}