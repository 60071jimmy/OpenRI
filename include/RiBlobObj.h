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

#ifndef __RI_BLOB_OBJ_HPP__
#define __RI_BLOB_OBJ_HPP__

typedef struct
{
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
} BlobObj_t;


#endif /* __RI_BLOB_OBJ_HPP__ */
