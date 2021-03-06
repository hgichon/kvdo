/*
 * Copyright (c) 2017 Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA. 
 *
 * $Id: //eng/uds-releases/flanders/src/uds/indexLayoutInternal.h#2 $
 */

#ifndef INDEX_LAYOUT_INTERNAL_H
#define INDEX_LAYOUT_INTERNAL_H

#include "indexLayout.h"

/**
 * Initialize the generic index layout data structure.
 *
 * @param layout        the generic index layout
 * @param ops           the specific layout operations for this index layout
 *
 * @return UDS_SUCCESS or an error code
 **/
int initIndexLayout(IndexLayout *layout, const IndexLayoutOps *ops);

#endif // INDEX_LAYOUT_INTERNAL_H
