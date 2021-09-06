/*
  The oSIP library implements the Session Initiation Protocol (SIP -rfc3261-)
  Copyright (C) 2001-2020 Aymeric MOIZARD amoizard@antisip.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <internal.h>

#include <osip_port.h>
#include <osip_fifo.h>

/* always use this method to initiate osip_fifo_t.
 */
void osip_fifo_init(osip_fifo_t *ff) {
  osip_list_init(&ff->queue);
  /* ff->nb_elt = 0; */
  ff->state = osip_empty;
}

int osip_fifo_add(osip_fifo_t *ff, void *el) {
  osip_list_add(&ff->queue, el, -1); /* insert at end of queue */
  ff->state = osip_ok;

  return OSIP_SUCCESS;
}

int osip_fifo_insert(osip_fifo_t *ff, void *el) {
  osip_list_add(&ff->queue, el, 0); /* insert at end of queue */
  ff->state = osip_ok;

  return OSIP_SUCCESS;
}

int osip_fifo_size(osip_fifo_t *ff) {
  int i;

  i = osip_list_size(&ff->queue);
  return i;
}

void *osip_fifo_get(osip_fifo_t *ff) {
  void *el = NULL;

  if (ff->state != osip_empty) {
    el = osip_list_get(&ff->queue, 0);
    osip_list_remove(&ff->queue, 0);
    /* ff->nb_elt--; */

  } else {
    OSIP_TRACE(osip_trace(__FILE__, __LINE__, OSIP_ERROR, NULL, "no element in fifo.\n"));
    return OSIP_SUCCESS; /* pile vide */
  }

  /* if (ff->nb_elt <= 0) */
  if (osip_list_size(&ff->queue) <= 0)
    ff->state = osip_empty;

  else
    ff->state = osip_ok;

  return el;
}

void *osip_fifo_tryget(osip_fifo_t *ff) {
  void *el = NULL;

  if (ff->state == osip_empty)
    return NULL;

  if (ff->state != osip_empty) {
    el = osip_list_get(&ff->queue, 0);
    osip_list_remove(&ff->queue, 0);
    /* ff->nb_elt--; */
  }

  /* if (ff->nb_elt <= 0) */
  if (osip_list_size(&ff->queue) <= 0)
    ff->state = osip_empty;

  else
    ff->state = osip_ok;

  return el;
}

void osip_fifo_free(osip_fifo_t *ff) {
  if (ff == NULL)
    return;

  osip_free(ff);
}
