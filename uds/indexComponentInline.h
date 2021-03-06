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
 * $Id: //eng/uds-releases/flanders/src/uds/indexComponentInline.h#2 $
 */

#ifndef INDEX_COMPONENT_INLINE_H
#define INDEX_COMPONENT_INLINE_H

#ifndef INDEX_COMPONENT_INLINE
# error "must be included by indexComponent.h"
#endif

#include "compiler.h"

typedef struct readPortal ReadPortal;
typedef struct writeZone  WriteZone;

typedef struct indexComponentOps {
  void (*freeMe)(IndexComponent *);
  int  (*openWriteRegion)(WriteZone *);
  int  (*cleanupWrite)(IndexComponent *);
  int  (*populateZones)(IndexComponent *);
  void (*freeZones)(IndexComponent *);
  int  (*prepareZones)(IndexComponent *, unsigned int);
  int  (*createReadPortal)(IndexComponent *, ReadPortal **);
  void (*freeReadPortal)(ReadPortal *);
  int  (*discard)(IndexComponent *);
} IndexComponentOps;

/**
 * The structure representing a savable (and loadable) part of an index.
 **/
struct indexComponent {
  const IndexComponentInfo  *info;          // IndexComponentInfo specification
  void                      *componentData; // The object to load or save
  void                      *context;       // The context used to load or save
  unsigned int               numZones;      // Number of zones in write portal
  WriteZone               **writeZones;     // State for writing component
  const IndexComponentOps   *ops;           // Operation table
};

/*****************************************************************************/
static INLINE void freeIndexComponent(IndexComponent **componentPtr)
{
  if (componentPtr == NULL || *componentPtr == NULL) {
    return;
  }
  (*componentPtr)->ops->freeMe(*componentPtr);
  *componentPtr = NULL;
}

/*****************************************************************************/
static INLINE const char *indexComponentName(IndexComponent *component)
{
  return component->info->name;
}

/*****************************************************************************/
static INLINE void *indexComponentData(IndexComponent *component)
{
  return component->componentData;
}

/*****************************************************************************/
static INLINE void *indexComponentContext(IndexComponent *component)
{
  return component->context;
}

/*****************************************************************************/
static INLINE const char *componentNameForPortal(ComponentPortal *portal)
{
  return indexComponentName(indexComponentForPortal(portal));
}

/*****************************************************************************/
static INLINE void *componentDataForPortal(ComponentPortal *portal)
{
  return indexComponentData(indexComponentForPortal(portal));
}

/*****************************************************************************/
static INLINE void *componentContextForPortal(ComponentPortal *portal)
{
  return indexComponentContext(indexComponentForPortal(portal));
}

/*****************************************************************************/
static INLINE bool skipIndexComponentOnCheckpoint(IndexComponent *component)
{
  return component->info->saveOnly;
}

/*****************************************************************************/
static INLINE bool
deferIndexComponentCheckpointToChapterWriter(IndexComponent *component)
{
  return component->info->chapterSync;
}

/*****************************************************************************/
static INLINE bool
missingIndexComponentRequiresReplay(IndexComponent *component)
{
  return component->info->saveOnly;
}

/*****************************************************************************/
static INLINE int discardIndexComponent(IndexComponent *component)
{
  return component->ops->discard(component);
}

#endif // INDEX_COMPONENT_INLINE_H
