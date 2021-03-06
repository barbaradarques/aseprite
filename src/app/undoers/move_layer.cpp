/* Aseprite
 * Copyright (C) 2001-2013  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/undoers/move_layer.h"

#include "raster/layer.h"
#include "undo/objects_container.h"
#include "undo/undoers_collector.h"

namespace app {
namespace undoers {

using namespace undo;

MoveLayer::MoveLayer(ObjectsContainer* objects, Layer* layer)
  : m_folderId(objects->addObject(layer->getParent()))
  , m_layerId(objects->addObject(layer))
{
  Layer* after = layer->getPrevious();

  m_afterId = (after ? objects->addObject(after): 0);
}

void MoveLayer::dispose()
{
  delete this;
}

void MoveLayer::revert(ObjectsContainer* objects, UndoersCollector* redoers)
{
  LayerFolder* folder = objects->getObjectT<LayerFolder>(m_folderId);
  Layer* layer = objects->getObjectT<Layer>(m_layerId);
  Layer* after = (m_afterId ? objects->getObjectT<Layer>(m_afterId): NULL);

  // Backup the current layer position
  redoers->pushUndoer(new MoveLayer(objects, layer));

  // Restack the layer
  folder->stackLayer(layer, after);
}

} // namespace undoers  
} // namespace app
