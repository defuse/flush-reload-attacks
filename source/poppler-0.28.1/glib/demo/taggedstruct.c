/*
 * Copyright (C) 2013 Igalia S.L.
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

#include <string.h>

#include "text.h"
#include "utils.h"

typedef struct {
  GtkWidget     *view;
  GtkTreeStore  *store;
  GtkWidget     *type_value;
  GtkWidget     *lang_value;
  GtkWidget     *abbr_value;
  GtkWidget     *id_value;
  GtkWidget     *title_value;
  GtkTextBuffer *text_buffer;
} PgdTaggedStructDemo;


static void
pgd_taggedstruct_free (PgdTaggedStructDemo *demo)
{
  if (!demo)
    return;

  if (demo->store)
    {
      g_object_unref (demo->store);
      demo->store = NULL;
    }

  g_free (demo);
}


static void
populate_store_aux (GtkTreeStore *store, GtkTreeIter *parent, PopplerStructureElementIter *iter)
{
  do
    {
      PopplerStructureElementIter *child = poppler_structure_element_iter_get_child (iter);
      PopplerStructureElement *element = poppler_structure_element_iter_get_element (iter);
      GEnumClass *enum_class = G_ENUM_CLASS (g_type_class_ref (POPPLER_TYPE_STRUCTURE_ELEMENT_KIND));
      GEnumValue *enum_value = g_enum_get_value (enum_class, poppler_structure_element_get_kind (element));
      GtkTreeIter pos;

      gtk_tree_store_append (store, &pos, parent);
      gtk_tree_store_set (store, &pos, 0, enum_value->value_nick, 1, element, -1);

      if (child)
        {
          populate_store_aux (store, &pos, child);
          poppler_structure_element_iter_free (child);
        }
    }
  while (poppler_structure_element_iter_next (iter));
}


static GtkTreeStore *
populate_store (PopplerStructureElementIter *iter)
{
  GtkTreeStore *store = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_POINTER);

  if (iter)
    {
      populate_store_aux (store, NULL, iter);
    }
  else
    {
      GtkTreeIter pos;

      gtk_tree_store_append (store, &pos, NULL);
      gtk_tree_store_set (store, &pos, 0, "<b>Not a Tagged-PDF</b>", 1, NULL, -1);
    }

  return store;
}


/*static void
pgd_row_activated (GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, PgdTaggedStructDemo *demo)
{*/
static void
pgd_selection_changed (GtkTreeSelection *selection, PgdTaggedStructDemo *demo)
{
  GtkTreeModel *model;
  PopplerStructureElement *element;
  GtkTreeIter iter;
  gpointer elementptr;

  if (!gtk_tree_selection_get_selected (selection, &model, &iter))
    return;

  gtk_tree_model_get (model, &iter, 1, &elementptr, -1);
  element = POPPLER_STRUCTURE_ELEMENT (elementptr);

  gtk_label_set_text (GTK_LABEL (demo->id_value),
                      poppler_structure_element_get_id (element));
  gtk_label_set_text (GTK_LABEL (demo->title_value),
                      poppler_structure_element_get_title (element));
  gtk_label_set_text (GTK_LABEL (demo->lang_value),
                      poppler_structure_element_get_language (element));
  gtk_label_set_text (GTK_LABEL (demo->abbr_value),
                      poppler_structure_element_get_abbreviation (element));
  gtk_text_buffer_set_text (demo->text_buffer, "", -1);

  if (poppler_structure_element_is_content (element))
    {
      const gchar *text = poppler_structure_element_get_text (element, FALSE);

      if (text)
        gtk_text_buffer_set_text (demo->text_buffer, text, -1);
      gtk_label_set_text (GTK_LABEL (demo->type_value), "Content");
    }
  else
    {
      if (poppler_structure_element_is_inline (element))
        gtk_label_set_text (GTK_LABEL (demo->type_value), "Inline");
      else if (poppler_structure_element_is_block (element))
        gtk_label_set_text (GTK_LABEL (demo->type_value), "Block");
      else
        gtk_label_set_text (GTK_LABEL (demo->type_value), "Structure");
    }
}


GtkWidget *
pgd_taggedstruct_create_widget (PopplerDocument *document)
{
  PopplerStructureElementIter *iter;
  PgdTaggedStructDemo *demo;
  GtkCellRenderer *renderer;
  GtkTreeSelection *selection;
  GtkWidget *hbox;
  GtkWidget *vbox;
  GtkWidget *grid;
  GtkWidget *scroll;
  GtkWidget *w;
  gint row;

  demo = g_new0 (PgdTaggedStructDemo, 1);

  iter = poppler_structure_element_iter_new (document);
  demo->store = populate_store (iter);
  poppler_structure_element_iter_free (iter);

  demo->view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (demo->store));

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (demo->view),
                                               0, "Type",
                                               renderer,
                                               "markup", 0,
                                               NULL);
  g_object_set (G_OBJECT (gtk_tree_view_get_column (GTK_TREE_VIEW (demo->view), 0)),
                "expand", TRUE, NULL);

  gtk_tree_view_expand_all (GTK_TREE_VIEW (demo->view));
  gtk_tree_view_set_show_expanders (GTK_TREE_VIEW (demo->view), TRUE);
  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (demo->view), TRUE);
  gtk_tree_view_set_headers_clickable (GTK_TREE_VIEW (demo->view), FALSE);
  gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW (demo->view), TRUE);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  scroll = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scroll), demo->view);
  gtk_widget_show (demo->view);
  gtk_box_pack_start (GTK_BOX (hbox), scroll, TRUE, TRUE, 0);
  gtk_widget_show (scroll);

  row = 0;
  grid = gtk_grid_new ();
  gtk_container_set_border_width (GTK_CONTAINER (grid), 12);
  gtk_grid_set_row_homogeneous (GTK_GRID (grid), FALSE);
  gtk_grid_set_column_spacing (GTK_GRID (grid), 6);
  gtk_grid_set_row_spacing (GTK_GRID (grid), 6);
  pgd_table_add_property_with_value_widget (GTK_GRID (grid), "<b>Type:</b>", &demo->type_value, NULL, &row);
  pgd_table_add_property_with_value_widget (GTK_GRID (grid), "<b>ID:</b>", &demo->id_value, NULL, &row);
  pgd_table_add_property_with_value_widget (GTK_GRID (grid), "<b>Title:</b>", &demo->title_value, NULL, &row);
  pgd_table_add_property_with_value_widget (GTK_GRID (grid), "<b>Language:</b>", &demo->lang_value, NULL, &row);
  pgd_table_add_property_with_value_widget (GTK_GRID (grid), "<b>Abbreviation:</b>", &demo->abbr_value, NULL, &row);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_box_pack_start (GTK_BOX (vbox), grid, FALSE, FALSE, 0);
  gtk_widget_show (grid);

  scroll = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (scroll), 12);
  gtk_box_pack_end (GTK_BOX (vbox), scroll, TRUE, TRUE, 0);
  gtk_widget_show (scroll);

  gtk_container_add (GTK_CONTAINER (scroll), (w = gtk_text_view_new ()));
  gtk_widget_show (w);

  demo->text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (w));
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (w), GTK_WRAP_WORD_CHAR);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (w), FALSE);
  gtk_text_buffer_set_text (demo->text_buffer, "", -1);
  gtk_widget_show (w);

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (demo->view));
  g_signal_connect (selection, "changed",
                    G_CALLBACK (pgd_selection_changed),
                    demo);

  gtk_box_pack_end (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
  gtk_widget_show (vbox);

  g_object_weak_ref (G_OBJECT (hbox),
                     (GWeakNotify) pgd_taggedstruct_free,
                     demo);

  gtk_widget_show (hbox);
  return hbox;
}
