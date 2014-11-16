/* poppler.cc: glib wrapper for poppler
 * Copyright (C) 2005, Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <config.h>
#include "poppler.h"

#ifndef __GI_SCANNER__
#include <Error.h>
#endif

GQuark poppler_error_quark (void)
{
  static GQuark q = 0;

  if (q == 0)
    q = g_quark_from_static_string ("poppler-quark");

  return q;
}

/**
 * poppler_get_backend:
 * 
 * Returns the backend compiled into the poppler library.
 * 
 * Return value: The backend used by poppler
 **/
PopplerBackend
poppler_get_backend (void)
{
  return POPPLER_BACKEND_CAIRO;
}

static const char poppler_version[] = PACKAGE_VERSION;

/**
 * poppler_get_version:
 * 
 * Returns the version of poppler in use.  This result is not to be freed.
 * 
 * Return value: the version of poppler.
 **/
const char *
poppler_get_version (void)
{
  return poppler_version;
}

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

/* We want to install an error callback so that PDF syntax warnings etc
 * can be redirected through the GLib logging API instead of always just
 * going to stderr.
 */

static void
error_cb (void *data G_GNUC_UNUSED,
          ErrorCategory category,
          Goffset pos,
          char *message)
{
  static const char * const cat_str[] = {
    "Syntax warning",
    "Syntax error",
    NULL,
    NULL,
    "IO error",
    NULL,
    "Unimplemented feature",
    "Internal error"
  };

  /* The following will never occur in poppler-glib */
  if (category == errConfig ||
      category == errCommandLine ||
      category == errNotAllowed)
    return;

  g_log (G_LOG_DOMAIN, G_LOG_LEVEL_INFO,
         "%s at position %" G_GOFFSET_FORMAT ": %s",
         cat_str[category], (goffset) pos, message);
}

static void __attribute__((__constructor__))
poppler_constructor (void)
{
  setErrorCallback (error_cb, NULL);
}

#endif /* GNUC */
