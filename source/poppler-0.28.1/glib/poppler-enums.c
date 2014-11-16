
/* Generated data (by glib-mkenums) */

#include <config.h>

#include "poppler-enums.h"

/* enumerations from "poppler-action.h" */
#include "poppler-action.h"
GType
poppler_action_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ACTION_UNKNOWN, "POPPLER_ACTION_UNKNOWN", "unknown" },
      { POPPLER_ACTION_NONE, "POPPLER_ACTION_NONE", "none" },
      { POPPLER_ACTION_GOTO_DEST, "POPPLER_ACTION_GOTO_DEST", "goto-dest" },
      { POPPLER_ACTION_GOTO_REMOTE, "POPPLER_ACTION_GOTO_REMOTE", "goto-remote" },
      { POPPLER_ACTION_LAUNCH, "POPPLER_ACTION_LAUNCH", "launch" },
      { POPPLER_ACTION_URI, "POPPLER_ACTION_URI", "uri" },
      { POPPLER_ACTION_NAMED, "POPPLER_ACTION_NAMED", "named" },
      { POPPLER_ACTION_MOVIE, "POPPLER_ACTION_MOVIE", "movie" },
      { POPPLER_ACTION_RENDITION, "POPPLER_ACTION_RENDITION", "rendition" },
      { POPPLER_ACTION_OCG_STATE, "POPPLER_ACTION_OCG_STATE", "ocg-state" },
      { POPPLER_ACTION_JAVASCRIPT, "POPPLER_ACTION_JAVASCRIPT", "javascript" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerActionType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_dest_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_DEST_UNKNOWN, "POPPLER_DEST_UNKNOWN", "unknown" },
      { POPPLER_DEST_XYZ, "POPPLER_DEST_XYZ", "xyz" },
      { POPPLER_DEST_FIT, "POPPLER_DEST_FIT", "fit" },
      { POPPLER_DEST_FITH, "POPPLER_DEST_FITH", "fith" },
      { POPPLER_DEST_FITV, "POPPLER_DEST_FITV", "fitv" },
      { POPPLER_DEST_FITR, "POPPLER_DEST_FITR", "fitr" },
      { POPPLER_DEST_FITB, "POPPLER_DEST_FITB", "fitb" },
      { POPPLER_DEST_FITBH, "POPPLER_DEST_FITBH", "fitbh" },
      { POPPLER_DEST_FITBV, "POPPLER_DEST_FITBV", "fitbv" },
      { POPPLER_DEST_NAMED, "POPPLER_DEST_NAMED", "named" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerDestType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_action_movie_operation_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ACTION_MOVIE_PLAY, "POPPLER_ACTION_MOVIE_PLAY", "play" },
      { POPPLER_ACTION_MOVIE_PAUSE, "POPPLER_ACTION_MOVIE_PAUSE", "pause" },
      { POPPLER_ACTION_MOVIE_RESUME, "POPPLER_ACTION_MOVIE_RESUME", "resume" },
      { POPPLER_ACTION_MOVIE_STOP, "POPPLER_ACTION_MOVIE_STOP", "stop" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerActionMovieOperation"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_action_layer_action_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ACTION_LAYER_ON, "POPPLER_ACTION_LAYER_ON", "on" },
      { POPPLER_ACTION_LAYER_OFF, "POPPLER_ACTION_LAYER_OFF", "off" },
      { POPPLER_ACTION_LAYER_TOGGLE, "POPPLER_ACTION_LAYER_TOGGLE", "toggle" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerActionLayerAction"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "poppler-document.h" */
#include "poppler-document.h"
GType
poppler_page_layout_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_PAGE_LAYOUT_UNSET, "POPPLER_PAGE_LAYOUT_UNSET", "unset" },
      { POPPLER_PAGE_LAYOUT_SINGLE_PAGE, "POPPLER_PAGE_LAYOUT_SINGLE_PAGE", "single-page" },
      { POPPLER_PAGE_LAYOUT_ONE_COLUMN, "POPPLER_PAGE_LAYOUT_ONE_COLUMN", "one-column" },
      { POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT, "POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT", "two-column-left" },
      { POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT, "POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT", "two-column-right" },
      { POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT, "POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT", "two-page-left" },
      { POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT, "POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT", "two-page-right" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerPageLayout"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_page_mode_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_PAGE_MODE_UNSET, "POPPLER_PAGE_MODE_UNSET", "unset" },
      { POPPLER_PAGE_MODE_NONE, "POPPLER_PAGE_MODE_NONE", "none" },
      { POPPLER_PAGE_MODE_USE_OUTLINES, "POPPLER_PAGE_MODE_USE_OUTLINES", "use-outlines" },
      { POPPLER_PAGE_MODE_USE_THUMBS, "POPPLER_PAGE_MODE_USE_THUMBS", "use-thumbs" },
      { POPPLER_PAGE_MODE_FULL_SCREEN, "POPPLER_PAGE_MODE_FULL_SCREEN", "full-screen" },
      { POPPLER_PAGE_MODE_USE_OC, "POPPLER_PAGE_MODE_USE_OC", "use-oc" },
      { POPPLER_PAGE_MODE_USE_ATTACHMENTS, "POPPLER_PAGE_MODE_USE_ATTACHMENTS", "use-attachments" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerPageMode"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_font_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_FONT_TYPE_UNKNOWN, "POPPLER_FONT_TYPE_UNKNOWN", "unknown" },
      { POPPLER_FONT_TYPE_TYPE1, "POPPLER_FONT_TYPE_TYPE1", "type1" },
      { POPPLER_FONT_TYPE_TYPE1C, "POPPLER_FONT_TYPE_TYPE1C", "type1c" },
      { POPPLER_FONT_TYPE_TYPE1COT, "POPPLER_FONT_TYPE_TYPE1COT", "type1cot" },
      { POPPLER_FONT_TYPE_TYPE3, "POPPLER_FONT_TYPE_TYPE3", "type3" },
      { POPPLER_FONT_TYPE_TRUETYPE, "POPPLER_FONT_TYPE_TRUETYPE", "truetype" },
      { POPPLER_FONT_TYPE_TRUETYPEOT, "POPPLER_FONT_TYPE_TRUETYPEOT", "truetypeot" },
      { POPPLER_FONT_TYPE_CID_TYPE0, "POPPLER_FONT_TYPE_CID_TYPE0", "cid-type0" },
      { POPPLER_FONT_TYPE_CID_TYPE0C, "POPPLER_FONT_TYPE_CID_TYPE0C", "cid-type0c" },
      { POPPLER_FONT_TYPE_CID_TYPE0COT, "POPPLER_FONT_TYPE_CID_TYPE0COT", "cid-type0cot" },
      { POPPLER_FONT_TYPE_CID_TYPE2, "POPPLER_FONT_TYPE_CID_TYPE2", "cid-type2" },
      { POPPLER_FONT_TYPE_CID_TYPE2OT, "POPPLER_FONT_TYPE_CID_TYPE2OT", "cid-type2ot" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerFontType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_viewer_preferences_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { POPPLER_VIEWER_PREFERENCES_UNSET, "POPPLER_VIEWER_PREFERENCES_UNSET", "unset" },
      { POPPLER_VIEWER_PREFERENCES_HIDE_TOOLBAR, "POPPLER_VIEWER_PREFERENCES_HIDE_TOOLBAR", "hide-toolbar" },
      { POPPLER_VIEWER_PREFERENCES_HIDE_MENUBAR, "POPPLER_VIEWER_PREFERENCES_HIDE_MENUBAR", "hide-menubar" },
      { POPPLER_VIEWER_PREFERENCES_HIDE_WINDOWUI, "POPPLER_VIEWER_PREFERENCES_HIDE_WINDOWUI", "hide-windowui" },
      { POPPLER_VIEWER_PREFERENCES_FIT_WINDOW, "POPPLER_VIEWER_PREFERENCES_FIT_WINDOW", "fit-window" },
      { POPPLER_VIEWER_PREFERENCES_CENTER_WINDOW, "POPPLER_VIEWER_PREFERENCES_CENTER_WINDOW", "center-window" },
      { POPPLER_VIEWER_PREFERENCES_DISPLAY_DOC_TITLE, "POPPLER_VIEWER_PREFERENCES_DISPLAY_DOC_TITLE", "display-doc-title" },
      { POPPLER_VIEWER_PREFERENCES_DIRECTION_RTL, "POPPLER_VIEWER_PREFERENCES_DIRECTION_RTL", "direction-rtl" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_flags_register_static (g_intern_static_string ("PopplerViewerPreferences"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_permissions_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { POPPLER_PERMISSIONS_OK_TO_PRINT, "POPPLER_PERMISSIONS_OK_TO_PRINT", "ok-to-print" },
      { POPPLER_PERMISSIONS_OK_TO_MODIFY, "POPPLER_PERMISSIONS_OK_TO_MODIFY", "ok-to-modify" },
      { POPPLER_PERMISSIONS_OK_TO_COPY, "POPPLER_PERMISSIONS_OK_TO_COPY", "ok-to-copy" },
      { POPPLER_PERMISSIONS_OK_TO_ADD_NOTES, "POPPLER_PERMISSIONS_OK_TO_ADD_NOTES", "ok-to-add-notes" },
      { POPPLER_PERMISSIONS_OK_TO_FILL_FORM, "POPPLER_PERMISSIONS_OK_TO_FILL_FORM", "ok-to-fill-form" },
      { POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS, "POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS", "ok-to-extract-contents" },
      { POPPLER_PERMISSIONS_OK_TO_ASSEMBLE, "POPPLER_PERMISSIONS_OK_TO_ASSEMBLE", "ok-to-assemble" },
      { POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION, "POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION", "ok-to-print-high-resolution" },
      { POPPLER_PERMISSIONS_FULL, "POPPLER_PERMISSIONS_FULL", "full" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_flags_register_static (g_intern_static_string ("PopplerPermissions"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "poppler-form-field.h" */
#include "poppler-form-field.h"
GType
poppler_form_field_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_FORM_FIELD_UNKNOWN, "POPPLER_FORM_FIELD_UNKNOWN", "unknown" },
      { POPPLER_FORM_FIELD_BUTTON, "POPPLER_FORM_FIELD_BUTTON", "button" },
      { POPPLER_FORM_FIELD_TEXT, "POPPLER_FORM_FIELD_TEXT", "text" },
      { POPPLER_FORM_FIELD_CHOICE, "POPPLER_FORM_FIELD_CHOICE", "choice" },
      { POPPLER_FORM_FIELD_SIGNATURE, "POPPLER_FORM_FIELD_SIGNATURE", "signature" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerFormFieldType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_form_button_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_FORM_BUTTON_PUSH, "POPPLER_FORM_BUTTON_PUSH", "push" },
      { POPPLER_FORM_BUTTON_CHECK, "POPPLER_FORM_BUTTON_CHECK", "check" },
      { POPPLER_FORM_BUTTON_RADIO, "POPPLER_FORM_BUTTON_RADIO", "radio" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerFormButtonType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_form_text_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_FORM_TEXT_NORMAL, "POPPLER_FORM_TEXT_NORMAL", "normal" },
      { POPPLER_FORM_TEXT_MULTILINE, "POPPLER_FORM_TEXT_MULTILINE", "multiline" },
      { POPPLER_FORM_TEXT_FILE_SELECT, "POPPLER_FORM_TEXT_FILE_SELECT", "file-select" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerFormTextType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_form_choice_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_FORM_CHOICE_COMBO, "POPPLER_FORM_CHOICE_COMBO", "combo" },
      { POPPLER_FORM_CHOICE_LIST, "POPPLER_FORM_CHOICE_LIST", "list" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerFormChoiceType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "poppler-annot.h" */
#include "poppler-annot.h"
GType
poppler_annot_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ANNOT_UNKNOWN, "POPPLER_ANNOT_UNKNOWN", "unknown" },
      { POPPLER_ANNOT_TEXT, "POPPLER_ANNOT_TEXT", "text" },
      { POPPLER_ANNOT_LINK, "POPPLER_ANNOT_LINK", "link" },
      { POPPLER_ANNOT_FREE_TEXT, "POPPLER_ANNOT_FREE_TEXT", "free-text" },
      { POPPLER_ANNOT_LINE, "POPPLER_ANNOT_LINE", "line" },
      { POPPLER_ANNOT_SQUARE, "POPPLER_ANNOT_SQUARE", "square" },
      { POPPLER_ANNOT_CIRCLE, "POPPLER_ANNOT_CIRCLE", "circle" },
      { POPPLER_ANNOT_POLYGON, "POPPLER_ANNOT_POLYGON", "polygon" },
      { POPPLER_ANNOT_POLY_LINE, "POPPLER_ANNOT_POLY_LINE", "poly-line" },
      { POPPLER_ANNOT_HIGHLIGHT, "POPPLER_ANNOT_HIGHLIGHT", "highlight" },
      { POPPLER_ANNOT_UNDERLINE, "POPPLER_ANNOT_UNDERLINE", "underline" },
      { POPPLER_ANNOT_SQUIGGLY, "POPPLER_ANNOT_SQUIGGLY", "squiggly" },
      { POPPLER_ANNOT_STRIKE_OUT, "POPPLER_ANNOT_STRIKE_OUT", "strike-out" },
      { POPPLER_ANNOT_STAMP, "POPPLER_ANNOT_STAMP", "stamp" },
      { POPPLER_ANNOT_CARET, "POPPLER_ANNOT_CARET", "caret" },
      { POPPLER_ANNOT_INK, "POPPLER_ANNOT_INK", "ink" },
      { POPPLER_ANNOT_POPUP, "POPPLER_ANNOT_POPUP", "popup" },
      { POPPLER_ANNOT_FILE_ATTACHMENT, "POPPLER_ANNOT_FILE_ATTACHMENT", "file-attachment" },
      { POPPLER_ANNOT_SOUND, "POPPLER_ANNOT_SOUND", "sound" },
      { POPPLER_ANNOT_MOVIE, "POPPLER_ANNOT_MOVIE", "movie" },
      { POPPLER_ANNOT_WIDGET, "POPPLER_ANNOT_WIDGET", "widget" },
      { POPPLER_ANNOT_SCREEN, "POPPLER_ANNOT_SCREEN", "screen" },
      { POPPLER_ANNOT_PRINTER_MARK, "POPPLER_ANNOT_PRINTER_MARK", "printer-mark" },
      { POPPLER_ANNOT_TRAP_NET, "POPPLER_ANNOT_TRAP_NET", "trap-net" },
      { POPPLER_ANNOT_WATERMARK, "POPPLER_ANNOT_WATERMARK", "watermark" },
      { POPPLER_ANNOT_3D, "POPPLER_ANNOT_3D", "3d" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerAnnotType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_annot_flag_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { POPPLER_ANNOT_FLAG_UNKNOWN, "POPPLER_ANNOT_FLAG_UNKNOWN", "unknown" },
      { POPPLER_ANNOT_FLAG_INVISIBLE, "POPPLER_ANNOT_FLAG_INVISIBLE", "invisible" },
      { POPPLER_ANNOT_FLAG_HIDDEN, "POPPLER_ANNOT_FLAG_HIDDEN", "hidden" },
      { POPPLER_ANNOT_FLAG_PRINT, "POPPLER_ANNOT_FLAG_PRINT", "print" },
      { POPPLER_ANNOT_FLAG_NO_ZOOM, "POPPLER_ANNOT_FLAG_NO_ZOOM", "no-zoom" },
      { POPPLER_ANNOT_FLAG_NO_ROTATE, "POPPLER_ANNOT_FLAG_NO_ROTATE", "no-rotate" },
      { POPPLER_ANNOT_FLAG_NO_VIEW, "POPPLER_ANNOT_FLAG_NO_VIEW", "no-view" },
      { POPPLER_ANNOT_FLAG_READ_ONLY, "POPPLER_ANNOT_FLAG_READ_ONLY", "read-only" },
      { POPPLER_ANNOT_FLAG_LOCKED, "POPPLER_ANNOT_FLAG_LOCKED", "locked" },
      { POPPLER_ANNOT_FLAG_TOGGLE_NO_VIEW, "POPPLER_ANNOT_FLAG_TOGGLE_NO_VIEW", "toggle-no-view" },
      { POPPLER_ANNOT_FLAG_LOCKED_CONTENTS, "POPPLER_ANNOT_FLAG_LOCKED_CONTENTS", "locked-contents" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_flags_register_static (g_intern_static_string ("PopplerAnnotFlag"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_annot_markup_reply_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ANNOT_MARKUP_REPLY_TYPE_R, "POPPLER_ANNOT_MARKUP_REPLY_TYPE_R", "r" },
      { POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP, "POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP", "group" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerAnnotMarkupReplyType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_annot_external_data_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D, "POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D", "3d" },
      { POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN, "POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN", "unknown" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerAnnotExternalDataType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_annot_text_state_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ANNOT_TEXT_STATE_MARKED, "POPPLER_ANNOT_TEXT_STATE_MARKED", "marked" },
      { POPPLER_ANNOT_TEXT_STATE_UNMARKED, "POPPLER_ANNOT_TEXT_STATE_UNMARKED", "unmarked" },
      { POPPLER_ANNOT_TEXT_STATE_ACCEPTED, "POPPLER_ANNOT_TEXT_STATE_ACCEPTED", "accepted" },
      { POPPLER_ANNOT_TEXT_STATE_REJECTED, "POPPLER_ANNOT_TEXT_STATE_REJECTED", "rejected" },
      { POPPLER_ANNOT_TEXT_STATE_CANCELLED, "POPPLER_ANNOT_TEXT_STATE_CANCELLED", "cancelled" },
      { POPPLER_ANNOT_TEXT_STATE_COMPLETED, "POPPLER_ANNOT_TEXT_STATE_COMPLETED", "completed" },
      { POPPLER_ANNOT_TEXT_STATE_NONE, "POPPLER_ANNOT_TEXT_STATE_NONE", "none" },
      { POPPLER_ANNOT_TEXT_STATE_UNKNOWN, "POPPLER_ANNOT_TEXT_STATE_UNKNOWN", "unknown" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerAnnotTextState"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_annot_free_text_quadding_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED, "POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED", "left-justified" },
      { POPPLER_ANNOT_FREE_TEXT_QUADDING_CENTERED, "POPPLER_ANNOT_FREE_TEXT_QUADDING_CENTERED", "centered" },
      { POPPLER_ANNOT_FREE_TEXT_QUADDING_RIGHT_JUSTIFIED, "POPPLER_ANNOT_FREE_TEXT_QUADDING_RIGHT_JUSTIFIED", "right-justified" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerAnnotFreeTextQuadding"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "poppler-structure-element.h" */
#include "poppler-structure-element.h"
GType
poppler_structure_element_kind_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_ELEMENT_CONTENT, "POPPLER_STRUCTURE_ELEMENT_CONTENT", "content" },
      { POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE, "POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE", "object-reference" },
      { POPPLER_STRUCTURE_ELEMENT_DOCUMENT, "POPPLER_STRUCTURE_ELEMENT_DOCUMENT", "document" },
      { POPPLER_STRUCTURE_ELEMENT_PART, "POPPLER_STRUCTURE_ELEMENT_PART", "part" },
      { POPPLER_STRUCTURE_ELEMENT_ARTICLE, "POPPLER_STRUCTURE_ELEMENT_ARTICLE", "article" },
      { POPPLER_STRUCTURE_ELEMENT_SECTION, "POPPLER_STRUCTURE_ELEMENT_SECTION", "section" },
      { POPPLER_STRUCTURE_ELEMENT_DIV, "POPPLER_STRUCTURE_ELEMENT_DIV", "div" },
      { POPPLER_STRUCTURE_ELEMENT_SPAN, "POPPLER_STRUCTURE_ELEMENT_SPAN", "span" },
      { POPPLER_STRUCTURE_ELEMENT_QUOTE, "POPPLER_STRUCTURE_ELEMENT_QUOTE", "quote" },
      { POPPLER_STRUCTURE_ELEMENT_NOTE, "POPPLER_STRUCTURE_ELEMENT_NOTE", "note" },
      { POPPLER_STRUCTURE_ELEMENT_REFERENCE, "POPPLER_STRUCTURE_ELEMENT_REFERENCE", "reference" },
      { POPPLER_STRUCTURE_ELEMENT_BIBENTRY, "POPPLER_STRUCTURE_ELEMENT_BIBENTRY", "bibentry" },
      { POPPLER_STRUCTURE_ELEMENT_CODE, "POPPLER_STRUCTURE_ELEMENT_CODE", "code" },
      { POPPLER_STRUCTURE_ELEMENT_LINK, "POPPLER_STRUCTURE_ELEMENT_LINK", "link" },
      { POPPLER_STRUCTURE_ELEMENT_ANNOT, "POPPLER_STRUCTURE_ELEMENT_ANNOT", "annot" },
      { POPPLER_STRUCTURE_ELEMENT_BLOCKQUOTE, "POPPLER_STRUCTURE_ELEMENT_BLOCKQUOTE", "blockquote" },
      { POPPLER_STRUCTURE_ELEMENT_CAPTION, "POPPLER_STRUCTURE_ELEMENT_CAPTION", "caption" },
      { POPPLER_STRUCTURE_ELEMENT_NONSTRUCT, "POPPLER_STRUCTURE_ELEMENT_NONSTRUCT", "nonstruct" },
      { POPPLER_STRUCTURE_ELEMENT_TOC, "POPPLER_STRUCTURE_ELEMENT_TOC", "toc" },
      { POPPLER_STRUCTURE_ELEMENT_TOC_ITEM, "POPPLER_STRUCTURE_ELEMENT_TOC_ITEM", "toc-item" },
      { POPPLER_STRUCTURE_ELEMENT_INDEX, "POPPLER_STRUCTURE_ELEMENT_INDEX", "index" },
      { POPPLER_STRUCTURE_ELEMENT_PRIVATE, "POPPLER_STRUCTURE_ELEMENT_PRIVATE", "private" },
      { POPPLER_STRUCTURE_ELEMENT_PARAGRAPH, "POPPLER_STRUCTURE_ELEMENT_PARAGRAPH", "paragraph" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING, "POPPLER_STRUCTURE_ELEMENT_HEADING", "heading" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING_1, "POPPLER_STRUCTURE_ELEMENT_HEADING_1", "heading-1" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING_2, "POPPLER_STRUCTURE_ELEMENT_HEADING_2", "heading-2" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING_3, "POPPLER_STRUCTURE_ELEMENT_HEADING_3", "heading-3" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING_4, "POPPLER_STRUCTURE_ELEMENT_HEADING_4", "heading-4" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING_5, "POPPLER_STRUCTURE_ELEMENT_HEADING_5", "heading-5" },
      { POPPLER_STRUCTURE_ELEMENT_HEADING_6, "POPPLER_STRUCTURE_ELEMENT_HEADING_6", "heading-6" },
      { POPPLER_STRUCTURE_ELEMENT_LIST, "POPPLER_STRUCTURE_ELEMENT_LIST", "list" },
      { POPPLER_STRUCTURE_ELEMENT_LIST_ITEM, "POPPLER_STRUCTURE_ELEMENT_LIST_ITEM", "list-item" },
      { POPPLER_STRUCTURE_ELEMENT_LIST_LABEL, "POPPLER_STRUCTURE_ELEMENT_LIST_LABEL", "list-label" },
      { POPPLER_STRUCTURE_ELEMENT_LIST_BODY, "POPPLER_STRUCTURE_ELEMENT_LIST_BODY", "list-body" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE, "POPPLER_STRUCTURE_ELEMENT_TABLE", "table" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE_ROW, "POPPLER_STRUCTURE_ELEMENT_TABLE_ROW", "table-row" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING, "POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING", "table-heading" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE_DATA, "POPPLER_STRUCTURE_ELEMENT_TABLE_DATA", "table-data" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER, "POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER", "table-header" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER, "POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER", "table-footer" },
      { POPPLER_STRUCTURE_ELEMENT_TABLE_BODY, "POPPLER_STRUCTURE_ELEMENT_TABLE_BODY", "table-body" },
      { POPPLER_STRUCTURE_ELEMENT_RUBY, "POPPLER_STRUCTURE_ELEMENT_RUBY", "ruby" },
      { POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT, "POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT", "ruby-base-text" },
      { POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT, "POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT", "ruby-annot-text" },
      { POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION, "POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION", "ruby-punctuation" },
      { POPPLER_STRUCTURE_ELEMENT_WARICHU, "POPPLER_STRUCTURE_ELEMENT_WARICHU", "warichu" },
      { POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT, "POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT", "warichu-text" },
      { POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION, "POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION", "warichu-punctuation" },
      { POPPLER_STRUCTURE_ELEMENT_FIGURE, "POPPLER_STRUCTURE_ELEMENT_FIGURE", "figure" },
      { POPPLER_STRUCTURE_ELEMENT_FORMULA, "POPPLER_STRUCTURE_ELEMENT_FORMULA", "formula" },
      { POPPLER_STRUCTURE_ELEMENT_FORM, "POPPLER_STRUCTURE_ELEMENT_FORM", "form" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureElementKind"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_get_text_flags_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { POPPLER_STRUCTURE_GET_TEXT_NONE, "POPPLER_STRUCTURE_GET_TEXT_NONE", "none" },
      { POPPLER_STRUCTURE_GET_TEXT_RECURSIVE, "POPPLER_STRUCTURE_GET_TEXT_RECURSIVE", "recursive" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_flags_register_static (g_intern_static_string ("PopplerStructureGetTextFlags"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_placement_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_PLACEMENT_BLOCK, "POPPLER_STRUCTURE_PLACEMENT_BLOCK", "block" },
      { POPPLER_STRUCTURE_PLACEMENT_INLINE, "POPPLER_STRUCTURE_PLACEMENT_INLINE", "inline" },
      { POPPLER_STRUCTURE_PLACEMENT_BEFORE, "POPPLER_STRUCTURE_PLACEMENT_BEFORE", "before" },
      { POPPLER_STRUCTURE_PLACEMENT_START, "POPPLER_STRUCTURE_PLACEMENT_START", "start" },
      { POPPLER_STRUCTURE_PLACEMENT_END, "POPPLER_STRUCTURE_PLACEMENT_END", "end" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructurePlacement"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_writing_mode_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_WRITING_MODE_LR_TB, "POPPLER_STRUCTURE_WRITING_MODE_LR_TB", "lr-tb" },
      { POPPLER_STRUCTURE_WRITING_MODE_RL_TB, "POPPLER_STRUCTURE_WRITING_MODE_RL_TB", "rl-tb" },
      { POPPLER_STRUCTURE_WRITING_MODE_TB_RL, "POPPLER_STRUCTURE_WRITING_MODE_TB_RL", "tb-rl" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureWritingMode"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_border_style_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_BORDER_STYLE_NONE, "POPPLER_STRUCTURE_BORDER_STYLE_NONE", "none" },
      { POPPLER_STRUCTURE_BORDER_STYLE_HIDDEN, "POPPLER_STRUCTURE_BORDER_STYLE_HIDDEN", "hidden" },
      { POPPLER_STRUCTURE_BORDER_STYLE_DOTTED, "POPPLER_STRUCTURE_BORDER_STYLE_DOTTED", "dotted" },
      { POPPLER_STRUCTURE_BORDER_STYLE_DASHED, "POPPLER_STRUCTURE_BORDER_STYLE_DASHED", "dashed" },
      { POPPLER_STRUCTURE_BORDER_STYLE_SOLID, "POPPLER_STRUCTURE_BORDER_STYLE_SOLID", "solid" },
      { POPPLER_STRUCTURE_BORDER_STYLE_DOUBLE, "POPPLER_STRUCTURE_BORDER_STYLE_DOUBLE", "double" },
      { POPPLER_STRUCTURE_BORDER_STYLE_GROOVE, "POPPLER_STRUCTURE_BORDER_STYLE_GROOVE", "groove" },
      { POPPLER_STRUCTURE_BORDER_STYLE_INSET, "POPPLER_STRUCTURE_BORDER_STYLE_INSET", "inset" },
      { POPPLER_STRUCTURE_BORDER_STYLE_OUTSET, "POPPLER_STRUCTURE_BORDER_STYLE_OUTSET", "outset" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureBorderStyle"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_text_align_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_TEXT_ALIGN_START, "POPPLER_STRUCTURE_TEXT_ALIGN_START", "start" },
      { POPPLER_STRUCTURE_TEXT_ALIGN_CENTER, "POPPLER_STRUCTURE_TEXT_ALIGN_CENTER", "center" },
      { POPPLER_STRUCTURE_TEXT_ALIGN_END, "POPPLER_STRUCTURE_TEXT_ALIGN_END", "end" },
      { POPPLER_STRUCTURE_TEXT_ALIGN_JUSTIFY, "POPPLER_STRUCTURE_TEXT_ALIGN_JUSTIFY", "justify" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureTextAlign"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_block_align_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_BLOCK_ALIGN_BEFORE, "POPPLER_STRUCTURE_BLOCK_ALIGN_BEFORE", "before" },
      { POPPLER_STRUCTURE_BLOCK_ALIGN_MIDDLE, "POPPLER_STRUCTURE_BLOCK_ALIGN_MIDDLE", "middle" },
      { POPPLER_STRUCTURE_BLOCK_ALIGN_AFTER, "POPPLER_STRUCTURE_BLOCK_ALIGN_AFTER", "after" },
      { POPPLER_STRUCTURE_BLOCK_ALIGN_JUSTIFY, "POPPLER_STRUCTURE_BLOCK_ALIGN_JUSTIFY", "justify" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureBlockAlign"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_inline_align_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_INLINE_ALIGN_START, "POPPLER_STRUCTURE_INLINE_ALIGN_START", "start" },
      { POPPLER_STRUCTURE_INLINE_ALIGN_CENTER, "POPPLER_STRUCTURE_INLINE_ALIGN_CENTER", "center" },
      { POPPLER_STRUCTURE_INLINE_ALIGN_END, "POPPLER_STRUCTURE_INLINE_ALIGN_END", "end" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureInlineAlign"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_text_decoration_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_TEXT_DECORATION_NONE, "POPPLER_STRUCTURE_TEXT_DECORATION_NONE", "none" },
      { POPPLER_STRUCTURE_TEXT_DECORATION_UNDERLINE, "POPPLER_STRUCTURE_TEXT_DECORATION_UNDERLINE", "underline" },
      { POPPLER_STRUCTURE_TEXT_DECORATION_OVERLINE, "POPPLER_STRUCTURE_TEXT_DECORATION_OVERLINE", "overline" },
      { POPPLER_STRUCTURE_TEXT_DECORATION_LINETHROUGH, "POPPLER_STRUCTURE_TEXT_DECORATION_LINETHROUGH", "linethrough" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureTextDecoration"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_ruby_align_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_RUBY_ALIGN_START, "POPPLER_STRUCTURE_RUBY_ALIGN_START", "start" },
      { POPPLER_STRUCTURE_RUBY_ALIGN_CENTER, "POPPLER_STRUCTURE_RUBY_ALIGN_CENTER", "center" },
      { POPPLER_STRUCTURE_RUBY_ALIGN_END, "POPPLER_STRUCTURE_RUBY_ALIGN_END", "end" },
      { POPPLER_STRUCTURE_RUBY_ALIGN_JUSTIFY, "POPPLER_STRUCTURE_RUBY_ALIGN_JUSTIFY", "justify" },
      { POPPLER_STRUCTURE_RUBY_ALIGN_DISTRIBUTE, "POPPLER_STRUCTURE_RUBY_ALIGN_DISTRIBUTE", "distribute" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureRubyAlign"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_ruby_position_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_RUBY_POSITION_BEFORE, "POPPLER_STRUCTURE_RUBY_POSITION_BEFORE", "before" },
      { POPPLER_STRUCTURE_RUBY_POSITION_AFTER, "POPPLER_STRUCTURE_RUBY_POSITION_AFTER", "after" },
      { POPPLER_STRUCTURE_RUBY_POSITION_WARICHU, "POPPLER_STRUCTURE_RUBY_POSITION_WARICHU", "warichu" },
      { POPPLER_STRUCTURE_RUBY_POSITION_INLINE, "POPPLER_STRUCTURE_RUBY_POSITION_INLINE", "inline" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureRubyPosition"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_glyph_orientation_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_GLYPH_ORIENTATION_AUTO, "POPPLER_STRUCTURE_GLYPH_ORIENTATION_AUTO", "auto" },
      { POPPLER_STRUCTURE_GLYPH_ORIENTATION_0, "POPPLER_STRUCTURE_GLYPH_ORIENTATION_0", "0" },
      { POPPLER_STRUCTURE_GLYPH_ORIENTATION_90, "POPPLER_STRUCTURE_GLYPH_ORIENTATION_90", "90" },
      { POPPLER_STRUCTURE_GLYPH_ORIENTATION_180, "POPPLER_STRUCTURE_GLYPH_ORIENTATION_180", "180" },
      { POPPLER_STRUCTURE_GLYPH_ORIENTATION_270, "POPPLER_STRUCTURE_GLYPH_ORIENTATION_270", "270" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureGlyphOrientation"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_list_numbering_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_LIST_NUMBERING_NONE, "POPPLER_STRUCTURE_LIST_NUMBERING_NONE", "none" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_DISC, "POPPLER_STRUCTURE_LIST_NUMBERING_DISC", "disc" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_CIRCLE, "POPPLER_STRUCTURE_LIST_NUMBERING_CIRCLE", "circle" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_SQUARE, "POPPLER_STRUCTURE_LIST_NUMBERING_SQUARE", "square" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_DECIMAL, "POPPLER_STRUCTURE_LIST_NUMBERING_DECIMAL", "decimal" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_UPPER_ROMAN, "POPPLER_STRUCTURE_LIST_NUMBERING_UPPER_ROMAN", "upper-roman" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_LOWER_ROMAN, "POPPLER_STRUCTURE_LIST_NUMBERING_LOWER_ROMAN", "lower-roman" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_UPPER_ALPHA, "POPPLER_STRUCTURE_LIST_NUMBERING_UPPER_ALPHA", "upper-alpha" },
      { POPPLER_STRUCTURE_LIST_NUMBERING_LOWER_ALPHA, "POPPLER_STRUCTURE_LIST_NUMBERING_LOWER_ALPHA", "lower-alpha" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureListNumbering"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_form_role_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED, "POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED", "undefined" },
      { POPPLER_STRUCTURE_FORM_ROLE_RADIO_BUTTON, "POPPLER_STRUCTURE_FORM_ROLE_RADIO_BUTTON", "radio-button" },
      { POPPLER_STRUCTURE_FORM_ROLE_PUSH_BUTTON, "POPPLER_STRUCTURE_FORM_ROLE_PUSH_BUTTON", "push-button" },
      { POPPLER_STRUCTURE_FORM_ROLE_TEXT_VALUE, "POPPLER_STRUCTURE_FORM_ROLE_TEXT_VALUE", "text-value" },
      { POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX, "POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX", "checkbox" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureFormRole"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_form_state_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_FORM_STATE_ON, "POPPLER_STRUCTURE_FORM_STATE_ON", "on" },
      { POPPLER_STRUCTURE_FORM_STATE_OFF, "POPPLER_STRUCTURE_FORM_STATE_OFF", "off" },
      { POPPLER_STRUCTURE_FORM_STATE_NEUTRAL, "POPPLER_STRUCTURE_FORM_STATE_NEUTRAL", "neutral" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureFormState"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_structure_table_scope_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_STRUCTURE_TABLE_SCOPE_ROW, "POPPLER_STRUCTURE_TABLE_SCOPE_ROW", "row" },
      { POPPLER_STRUCTURE_TABLE_SCOPE_COLUMN, "POPPLER_STRUCTURE_TABLE_SCOPE_COLUMN", "column" },
      { POPPLER_STRUCTURE_TABLE_SCOPE_BOTH, "POPPLER_STRUCTURE_TABLE_SCOPE_BOTH", "both" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerStructureTableScope"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "poppler.h" */
#include "poppler.h"
GType
poppler_error_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ERROR_INVALID, "POPPLER_ERROR_INVALID", "invalid" },
      { POPPLER_ERROR_ENCRYPTED, "POPPLER_ERROR_ENCRYPTED", "encrypted" },
      { POPPLER_ERROR_OPEN_FILE, "POPPLER_ERROR_OPEN_FILE", "open-file" },
      { POPPLER_ERROR_BAD_CATALOG, "POPPLER_ERROR_BAD_CATALOG", "bad-catalog" },
      { POPPLER_ERROR_DAMAGED, "POPPLER_ERROR_DAMAGED", "damaged" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerError"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_orientation_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_ORIENTATION_PORTRAIT, "POPPLER_ORIENTATION_PORTRAIT", "portrait" },
      { POPPLER_ORIENTATION_LANDSCAPE, "POPPLER_ORIENTATION_LANDSCAPE", "landscape" },
      { POPPLER_ORIENTATION_UPSIDEDOWN, "POPPLER_ORIENTATION_UPSIDEDOWN", "upsidedown" },
      { POPPLER_ORIENTATION_SEASCAPE, "POPPLER_ORIENTATION_SEASCAPE", "seascape" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerOrientation"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_page_transition_type_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_PAGE_TRANSITION_REPLACE, "POPPLER_PAGE_TRANSITION_REPLACE", "replace" },
      { POPPLER_PAGE_TRANSITION_SPLIT, "POPPLER_PAGE_TRANSITION_SPLIT", "split" },
      { POPPLER_PAGE_TRANSITION_BLINDS, "POPPLER_PAGE_TRANSITION_BLINDS", "blinds" },
      { POPPLER_PAGE_TRANSITION_BOX, "POPPLER_PAGE_TRANSITION_BOX", "box" },
      { POPPLER_PAGE_TRANSITION_WIPE, "POPPLER_PAGE_TRANSITION_WIPE", "wipe" },
      { POPPLER_PAGE_TRANSITION_DISSOLVE, "POPPLER_PAGE_TRANSITION_DISSOLVE", "dissolve" },
      { POPPLER_PAGE_TRANSITION_GLITTER, "POPPLER_PAGE_TRANSITION_GLITTER", "glitter" },
      { POPPLER_PAGE_TRANSITION_FLY, "POPPLER_PAGE_TRANSITION_FLY", "fly" },
      { POPPLER_PAGE_TRANSITION_PUSH, "POPPLER_PAGE_TRANSITION_PUSH", "push" },
      { POPPLER_PAGE_TRANSITION_COVER, "POPPLER_PAGE_TRANSITION_COVER", "cover" },
      { POPPLER_PAGE_TRANSITION_UNCOVER, "POPPLER_PAGE_TRANSITION_UNCOVER", "uncover" },
      { POPPLER_PAGE_TRANSITION_FADE, "POPPLER_PAGE_TRANSITION_FADE", "fade" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerPageTransitionType"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_page_transition_alignment_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_PAGE_TRANSITION_HORIZONTAL, "POPPLER_PAGE_TRANSITION_HORIZONTAL", "horizontal" },
      { POPPLER_PAGE_TRANSITION_VERTICAL, "POPPLER_PAGE_TRANSITION_VERTICAL", "vertical" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerPageTransitionAlignment"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_page_transition_direction_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_PAGE_TRANSITION_INWARD, "POPPLER_PAGE_TRANSITION_INWARD", "inward" },
      { POPPLER_PAGE_TRANSITION_OUTWARD, "POPPLER_PAGE_TRANSITION_OUTWARD", "outward" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerPageTransitionDirection"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_selection_style_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_SELECTION_GLYPH, "POPPLER_SELECTION_GLYPH", "glyph" },
      { POPPLER_SELECTION_WORD, "POPPLER_SELECTION_WORD", "word" },
      { POPPLER_SELECTION_LINE, "POPPLER_SELECTION_LINE", "line" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerSelectionStyle"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_print_flags_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { POPPLER_PRINT_DOCUMENT, "POPPLER_PRINT_DOCUMENT", "document" },
      { POPPLER_PRINT_MARKUP_ANNOTS, "POPPLER_PRINT_MARKUP_ANNOTS", "markup-annots" },
      { POPPLER_PRINT_STAMP_ANNOTS_ONLY, "POPPLER_PRINT_STAMP_ANNOTS_ONLY", "stamp-annots-only" },
      { POPPLER_PRINT_ALL, "POPPLER_PRINT_ALL", "all" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_flags_register_static (g_intern_static_string ("PopplerPrintFlags"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_find_flags_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { POPPLER_FIND_DEFAULT, "POPPLER_FIND_DEFAULT", "default" },
      { POPPLER_FIND_CASE_SENSITIVE, "POPPLER_FIND_CASE_SENSITIVE", "case-sensitive" },
      { POPPLER_FIND_BACKWARDS, "POPPLER_FIND_BACKWARDS", "backwards" },
      { POPPLER_FIND_WHOLE_WORDS_ONLY, "POPPLER_FIND_WHOLE_WORDS_ONLY", "whole-words-only" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_flags_register_static (g_intern_static_string ("PopplerFindFlags"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
poppler_backend_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { POPPLER_BACKEND_UNKNOWN, "POPPLER_BACKEND_UNKNOWN", "unknown" },
      { POPPLER_BACKEND_SPLASH, "POPPLER_BACKEND_SPLASH", "splash" },
      { POPPLER_BACKEND_CAIRO, "POPPLER_BACKEND_CAIRO", "cairo" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = 
       g_enum_register_static (g_intern_static_string ("PopplerBackend"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}



/* Generated data ends here */

