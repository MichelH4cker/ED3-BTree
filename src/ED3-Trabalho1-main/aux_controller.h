#ifndef __AUX_CONTROLLER_H__
#define __AUX_CONTROLLER_H__

#include "main.h"

/**
 * @brief 
 * 
 * @param filter 
 */
void filterConstructor(struct filter filter);

/**
 * @brief 
 * 
 * @param field_key 
 * @return int 
 */
int itsInteger(int field_key);

/**
 * @brief 
 * 
 * @param fieldName 
 * @return int 
 */
int selectFieldKey(char fieldName[]);

/**
 * @brief Set the array filters object
 * 
 * @param array_filter 
 * @param n 
 */
void set_array_filters(struct filter array_filter[], int n);

#endif
