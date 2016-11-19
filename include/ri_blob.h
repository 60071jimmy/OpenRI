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

#ifndef __RI_BLOB_H__
#define __RI_BLOB_H__

#include "openri.h"

#include <vector>
#include <opencv2\opencv.hpp>
#include <vector>	


using namespace std;	// For vector.
using namespace cv;


typedef struct {
    int x;
    int y;
    unsigned char gray;
} RiBlobPoint_t;

typedef struct {
    int tag;
    int area;
    unsigned char grayAvg;
    int xMax;
	int xMin;
	int yMax;
	int yMin;
    int width;
	int height;
    int xCenter;
	int yCenter;
	int xCenterTotal;
	int yCenterTotal;	// Used to calculate x,yCenter.
	int grayTotal;	// Used to calculate grayAvg.
	int examined;
} RiBlobObj_t;

typedef struct {
	unsigned short *tagMap;	

	vector<RiBlobObj_t> blobObjs;

	int width;
	int height;

	int isGrayAvgEnabled;
	int isCenterXyEnabled;			// Indicate whether need to calculate these values. 

	//thresholds that one blob can be considered Pass.
	//use setThreshold() to update value. 
	unsigned char grayMin;
	unsigned char grayMax;
	int widthMax;
	int widthMin;
	int heightMax;
	int heightMin;				
	int areaMax;
	int areaMin;
} RiBlob_t;


	RI_API vector<RiBlobObj_t> getRiBlobObjs(RiBlob_t* riBlob);
	RI_API unsigned short* getTagMap(RiBlob_t* riBlob);

	RI_API int RiBlob_New(RiBlob_t* riBlob);
	RI_API int RiBlob_Free(RiBlob_t* riBlob);

	RI_API int findBlob(Mat *matSrc, Mat *matDst);

	RI_API int RiBlob_EnableGrayAvg(RiBlob_t* riBlob, int isGrayAvgEnabled);
	RI_API int RiBlob_EnableCenterXy(RiBlob_t* riBlob, int isCenterXyEnabled);

	RI_API int setThresholds(RiBlob_t* riBlob, unsigned char grayMin = 255, unsigned char grayMax = 255, int widthMin = 0, int widthMax = INT_MAX, int heightMin = 0, int widthHeight = INT_MAX, int areaMin = 0, int areaMax = INT_MAX);
	
	RI_API int sortTagByXmin(vector<RiBlobObj_t> *inputBlobs, int rowOffset);
	RI_API int sortTagByXmin(vector<RiBlobObj_t> *inputBlobs);
	RI_API int sortTagByArea(vector<RiBlobObj_t> *inputBlobs);

	RI_API int filterBlobs(RiBlob_t* riBlob, Mat *matSrc);
	RI_API int colorBlob( Mat *matSrc, Mat *matDst);
	RI_API int countAndPrint(RiBlob_t* riBlob, Mat *matSrc, Mat *matDst);


#endif /* __RI_BLOB_H__ */
