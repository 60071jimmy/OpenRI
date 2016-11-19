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

#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#if defined(RI_WINDOWS)
  #include <windows.h>
  #include <locale.h>
#elif defined(RI_LINUX) 

#endif

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

static const ri_utf8 ri_utf8_skip_data[256] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1
};

const ri_utf8 *riUtf8Skip = ri_utf8_skip_data;

#define riUtf8_NextChar(p) (ri_utf8 *)((p) + riUtf8Skip[*(const ri_uchar *)(p)])


RI_API ri_utf8 *RiUtf8_NextChar(const ri_utf8 *str) {
  if (str == NULL) return NULL;
    
  return  (ri_utf8 *)riUtf8_NextChar(str);
}

RI_API int RiUtf8_GetLength(const ri_utf8 *str) {
  ri_int len;
//  const ri_utf8 *start;
  ri_utf8 *str_ptr;

  if (str == NULL) return 0;  
  if (str[0] == '\0') return 0; 
  
  str_ptr = (ri_utf8 *)str;
  
  len = 0;
//  start = str;        

  while (*str_ptr) { 
    len++;
       
    str_ptr = riUtf8_NextChar(str_ptr);            
  }

  return len;
}

RI_API int RiUtf8_GetSize(const ri_utf8 *str) {
  ri_int size;
  const ri_utf8 *start;
  ri_utf8 *str_ptr;
  
  if (str == NULL) return 0;
  if (str[0] == '\0') return 0;
  
  size = 0;
  start = str;
  str_ptr = (ri_utf8 *)str;        

  while (*str_ptr) {
    str_ptr = riUtf8_NextChar(str_ptr);          
  }
  
  size = (int)(str_ptr - start);
  
  return size;  
}

RI_API int RiUtf8_ToWchar(wchar_t *wstr, ri_int wstr_length, const ri_utf8 *str) {
  int len;
  if (wstr == NULL) return RI_ERROR_PARAMETER_0;
  if (wstr_length <= 0) return RI_ERROR_PARAMETER_1;
    
  wstr[0] = 0;
  if (str == NULL) return RI_ERROR_PARAMETER_2;
    
  if (RiUtf8_GetLength(str) == 0) {
    return RI_ERROR_PARAMETER_2;    
  }

#if defined(RI_CONFIG_VC)
  len = MultiByteToWideChar(CP_UTF8, 
                            0,         
                            str, 
                            -1,  // Byte length.       
                            wstr,  
                            wstr_length * sizeof(wchar_t));  
#else
  len = (int)mbstowcs(wstr, (const char*)str, wstr_length);
#endif   

  return len;                        
}

RI_API int RiUtf8_FromWchar(ri_utf8 *str, ri_int str_size, const wchar_t *wstr) {
  if (str == NULL) return RI_ERROR_PARAMETER_0;
  if (str_size <= 0) return RI_ERROR_PARAMETER_1;
  str[0] = 0;
  if (wstr == NULL) return RI_ERROR_PARAMETER_2;

  if (wcslen(wstr) == 0) {
    return RI_ERROR_PARAMETER_2;    
  }
  
#if defined(RI_VC)   
  WideCharToMultiByte(CP_ACP, 
                      0, 
                      wstr,
                      (ri_int)wcslen(wstr), 
                      (LPSTR)str, 
                      str_size,
                      NULL,    
                      NULL);  
#else
  wcsrtombs((char*)str, &wstr, str_size, NULL);
#endif                      
  
  return RI_OK;                        
}

RI_API int RiUtf8_ToLowerCase(ri_utf8 *str) {
  if (str == NULL) return RI_ERROR_NULL_POINTER;

  while (*str) {
    switch(*str) {
      case 'A': *str = 'a'; break;
      case 'B': *str = 'b'; break;
      case 'C': *str = 'c'; break;
      case 'D': *str = 'd'; break;
      case 'E': *str = 'e'; break;
      case 'F': *str = 'f'; break;
      case 'G': *str = 'g'; break;
      case 'H': *str = 'h'; break;
      case 'I': *str = 'i'; break;
      case 'J': *str = 'j'; break;
      case 'K': *str = 'k'; break;
      case 'L': *str = 'l'; break;
      case 'M': *str = 'm'; break;
      case 'N': *str = 'n'; break;
      case 'O': *str = 'o'; break;
      case 'P': *str = 'p'; break;
      case 'Q': *str = 'q'; break;
      case 'R': *str = 'r'; break;
      case 'S': *str = 's'; break;
      case 'T': *str = 't'; break;
      case 'U': *str = 'u'; break;
      case 'V': *str = 'v'; break;
      case 'W': *str = 'w'; break;
      case 'X': *str = 'x'; break;
      case 'Y': *str = 'y'; break;
      case 'Z': *str = 'z'; break;                                                                          
    }
    
    str = riUtf8_NextChar(str);
  }  

  return RI_OK;  
}

RI_API int RiUtf8_ToUpperCase(ri_utf8 *str) {
  if (str == NULL) return RI_ERROR_NULL_POINTER;

  while (*str) {
    switch(*str) {
      case 'a': *str = 'A'; break;
      case 'b': *str = 'B'; break;
      case 'c': *str = 'C'; break;
      case 'd': *str = 'D'; break;
      case 'e': *str = 'E'; break;
      case 'f': *str = 'F'; break;
      case 'g': *str = 'G'; break;
      case 'h': *str = 'H'; break;
      case 'i': *str = 'I'; break;
      case 'j': *str = 'J'; break;
      case 'k': *str = 'K'; break;
      case 'l': *str = 'L'; break;
      case 'm': *str = 'M'; break;
      case 'n': *str = 'N'; break;
      case 'o': *str = 'O'; break;
      case 'p': *str = 'P'; break;
      case 'q': *str = 'Q'; break;
      case 'r': *str = 'R'; break;
      case 's': *str = 'S'; break;
      case 't': *str = 'T'; break;
      case 'u': *str = 'U'; break;
      case 'v': *str = 'V'; break;
      case 'w': *str = 'W'; break;
      case 'x': *str = 'X'; break;
      case 'y': *str = 'Y'; break;
      case 'z': *str = 'Z'; break;                                                                          
    }
    
    str = riUtf8_NextChar(str);
  }
  return RI_OK;  
}

RI_API int RiUtf8_GetIndexShift(const ri_utf8 *str, int index) { 
  ri_int shift;
  ri_int count;
  ri_int str_length;
  ri_utf8 *str_ptr;
  const ri_utf8 *start;
  
  if (str == NULL) return RI_ERROR_PARAMETER_0;
  if (index < 0) return RI_ERROR_PARAMETER_1;

  if (index == 0) return 0;
  
  str_length = RiUtf8_GetLength(str);
  if (index >= str_length) {
    return RI_ERROR_PARAMETER_1;
  }
  
  shift = 0;
  count = 0;  
  str_ptr = (ri_utf8 *)str;
  start = str;  

  while (*str_ptr) {
    str_ptr = riUtf8_NextChar(str_ptr);
    count ++;
    
    if (count >= index)
      break;
  }
  
  shift = (int)(str_ptr - start);

  return shift; 
}

RI_API int RiUtf8_GetIndex(const ri_utf8 *str, const ri_utf8 *str_find) {
  ri_int index;
  ri_int search_length;
  ri_int  str_size;
  ri_int  str_length;
  ri_int  str_find_size;  
  ri_int  str_find_length;
  ri_utf8 *str_ptr_from;  
  
  if (str == NULL) return RI_ERROR_PARAMETER_0;
  if (str_find == NULL) return RI_ERROR_PARAMETER_1;

  str_size      = RiUtf8_GetSize(str);
  str_find_size = RiUtf8_GetSize(str_find);
  
  if (str_find_size > str_size) {
    return RI_ERROR_PARAMETER_1;
  }
  
  str_length = RiUtf8_GetLength(str);
  str_find_length = RiUtf8_GetLength(str_find);
  
  if (str_find_length > str_length) {
    return RI_ERROR_PARAMETER_1;
  }
  
  index = 0;
  str_ptr_from = (ri_utf8 *)str;
  search_length = str_length - str_find_length;
  
  while (index <= search_length) {        
    if (ri_memcmp(str_ptr_from, str_find, str_find_size) == 0) {
      break;
    }

    str_ptr_from = riUtf8_NextChar(str_ptr_from);    
    index ++;
  }   
  
	// Not found.
	if (index > search_length) {
		index = RI_ERROR_NOT_FOUND;
	}
  
  return index;
}

RI_API int RiUtf8_GetLastIndex(const ri_utf8 *str, const ri_utf8 *str_find) {
  ri_int index;
  ri_int last_index;
  ri_utf8 *str_ptr;
  
  if (str == NULL) return RI_ERROR_PARAMETER_0;
  if (str_find == NULL) return RI_ERROR_PARAMETER_1;
  
  index = RiUtf8_GetIndex(str, str_find);
  if (index < 0) {
    return index;
  }
  
  while (index >= 0) {
    last_index = index;
    str_ptr = (ri_utf8 *)(str + RiUtf8_GetIndexShift(str, index));
    str_ptr = riUtf8_NextChar(str_ptr);
    index = RiUtf8_GetIndex(str_ptr, str_find);
  }
  
  last_index = RiUtf8_GetLength(str) - last_index - 1;
 
  return last_index;
}

RI_API int RiUtf8_GetChar(const ri_utf8 *str, ri_int index, ri_utf8 *char_buf, ri_int char_buf_size) {
  int *this_char;
  int *next_char;
  int  this_char_size;
  ri_int  i;
  
  if (char_buf == NULL)    return RI_ERROR_PARAMETER_2;
  if (char_buf_size == 0)  return RI_ERROR_PARAMETER_3;
  
  ri_memset(char_buf, 0, char_buf_size);  // Cannot use char_buf[0] = 0; !!!
  
  if (str == NULL)  return RI_ERROR_PARAMETER_0;
  
  if (RiUtf8_GetLength(str) <= index)  return RI_ERROR_PARAMETER_1;
    
  this_char = (int *)str;
  
  for (i = 0; i < index; i ++) {
    this_char = (this_char);
  }
  
  next_char = (this_char);
  
  if (this_char == NULL || next_char == NULL) {
    return RI_ERROR; 
  }
  
  this_char_size = *next_char - *this_char;
  
  if (this_char_size <= 0) {
    return RI_ERROR;
  }
  
  ri_memcpy(char_buf, this_char, this_char_size);
    
  return RI_OK;
}

RI_API int RiUtf8_SubString(ri_utf8 *str_to, ri_int str_to_size, const ri_utf8 *str_from, ri_int from, ri_int to) {
  ri_int  str_from_len;
  ri_int shift_from;
  ri_int shift_to;
  ri_int copy_size;
  
  if (str_to == NULL) return RI_ERROR_PARAMETER_0;
  if (str_to_size == 0) return RI_ERROR_PARAMETER_1;

  str_to[0] = 0;
  if (str_from == NULL) return RI_ERROR_PARAMETER_2;
  if (from > to) return RI_ERROR_PARAMETER_3;  
  str_from_len = RiUtf8_GetLength(str_from);
  if (str_from_len == 0) return RI_ERROR_PARAMETER_2;
  if (to > str_from_len) return RI_ERROR_PARAMETER_4;  
  
  shift_from = RiUtf8_GetIndexShift(str_from, from);
  if (shift_from < 0) {
    return RI_ERROR; 
  }
  
  shift_to = RiUtf8_GetIndexShift(str_from, to);
  if (shift_to < 0) {
    return RI_ERROR_PARAMETER_4; 
  }
  
  copy_size = shift_to - shift_from;
  if (copy_size < 0 || ((copy_size + 1) > str_to_size)) {
    return RI_ERROR_PARAMETER_4; 
  }
  
  ri_memcpy(str_to, str_from + shift_from, copy_size);
  str_to[copy_size] = 0;

  return RI_OK;
}

RI_API ri_utf8 *RiUtf8_GetCharAddress(const ri_utf8 *str, ri_int index) {
  ri_utf8 *thisChar;
  ri_int  i;

  if (str == NULL)  return NULL;
  
  if (RiUtf8_GetLength(str) <= index)  return NULL;
    
  thisChar = (ri_utf8 *)str;
  
  for (i = 0; i < index; i ++) {
    thisChar = riUtf8_NextChar(thisChar);
  }
  
  return thisChar;
}

#ifdef __cplusplus
}
#endif
