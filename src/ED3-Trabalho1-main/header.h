#ifndef __HEADER_H__
#define __HEADER_H__

#include "main.h"

/**
 * @brief 
 * 
 * @param fp 
 * @param current_header 
 * @return struct header 
 */
struct header returnCurrentHeader(FILE *fp, struct header current_header);

/**
 * @brief 
 * 
 * @param fp 
 * @param header 
 */
void updateHeader(FILE *fp, struct header header);

/**
 * @brief Create a Header object
 * 
 * @param fp 
 * @param header 
 */
void createHeader(FILE *fp, struct header header);

#endif