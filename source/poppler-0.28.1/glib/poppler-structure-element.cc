/* poppler-structure.cc: glib interface to poppler
 *
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

#include "config.h"

#ifndef __GI_SCANNER__
#include <StructTreeRoot.h>
#include <StructElement.h>
#include <GlobalParams.h>
#include <UnicodeMap.h>
#include <math.h>
#endif /* !__GI_SCANNER__ */

#include "poppler.h"
#include "poppler-private.h"
#include "poppler-structure-element.h"


/**
 * SECTION:poppler-structure-element
 * @short_description: Document structure element.
 * @title: PopplerStructureElement
 * @see_also: #PopplerStructure
 *
 * Instances of #PopplerStructureElement are used to describe the structure
 * of a #PopplerDocument. To access the elements in the structure of the
 * document, use poppler_structure_element_iter_new() to obtain an iterator
 * for the top-level #PopplerStructure, and then use the
 * #PopplerStructureElementIter methods to traverse the structure tree.
 */

typedef struct _PopplerStructureElementClass
{
  GObjectClass parent_class;
} PopplerStructureElementClass;

G_DEFINE_TYPE (PopplerStructureElement, poppler_structure_element, G_TYPE_OBJECT);

static PopplerStructureElement *
_poppler_structure_element_new (PopplerDocument *document, StructElement *element)
{
  PopplerStructureElement *poppler_structure_element;

  g_assert (POPPLER_IS_DOCUMENT (document));
  g_assert (element);

  poppler_structure_element = (PopplerStructureElement *) g_object_new (POPPLER_TYPE_STRUCTURE_ELEMENT, NULL, NULL);
  poppler_structure_element->document = (PopplerDocument *) g_object_ref (document);
  poppler_structure_element->elem = element;

  return poppler_structure_element;
}


static void
poppler_structure_element_init (PopplerStructureElement *poppler_structure_element)
{
}


static void
poppler_structure_element_finalize (GObject *object)
{
  PopplerStructureElement *poppler_structure_element = POPPLER_STRUCTURE_ELEMENT (object);

  /* poppler_structure_element->elem is owned by the StructTreeRoot */
  g_object_unref (poppler_structure_element->document);

  G_OBJECT_CLASS (poppler_structure_element_parent_class)->finalize (object);
}


static void
poppler_structure_element_class_init (PopplerStructureElementClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = poppler_structure_element_finalize;
}


/**
 * poppler_structure_element_get_kind:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Return value: A #PopplerStructureElementKind value.
 *
 * Since: 0.26
 */
PopplerStructureElementKind
poppler_structure_element_get_kind (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_CONTENT);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, POPPLER_STRUCTURE_ELEMENT_CONTENT);

  switch (poppler_structure_element->elem->getType ())
    {
      case StructElement::MCID:
        return POPPLER_STRUCTURE_ELEMENT_CONTENT;
      case StructElement::OBJR:
        return POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE;
      case StructElement::Document:
        return POPPLER_STRUCTURE_ELEMENT_DOCUMENT;
      case StructElement::Part:
        return POPPLER_STRUCTURE_ELEMENT_PART;
      case StructElement::Art:
        return POPPLER_STRUCTURE_ELEMENT_ARTICLE;
      case StructElement::Sect:
        return POPPLER_STRUCTURE_ELEMENT_SECTION;
      case StructElement::Div:
        return POPPLER_STRUCTURE_ELEMENT_DIV;
      case StructElement::Span:
        return POPPLER_STRUCTURE_ELEMENT_SPAN;
      case StructElement::Quote:
        return POPPLER_STRUCTURE_ELEMENT_QUOTE;
      case StructElement::Note:
        return POPPLER_STRUCTURE_ELEMENT_NOTE;
      case StructElement::Reference:
        return POPPLER_STRUCTURE_ELEMENT_REFERENCE;
      case StructElement::BibEntry:
        return POPPLER_STRUCTURE_ELEMENT_BIBENTRY;
      case StructElement::Code:
        return POPPLER_STRUCTURE_ELEMENT_CODE;
      case StructElement::Link:
        return POPPLER_STRUCTURE_ELEMENT_LINK;
      case StructElement::Annot:
        return POPPLER_STRUCTURE_ELEMENT_ANNOT;
      case StructElement::BlockQuote:
        return POPPLER_STRUCTURE_ELEMENT_BLOCKQUOTE;
      case StructElement::Caption:
        return POPPLER_STRUCTURE_ELEMENT_CAPTION;
      case StructElement::NonStruct:
        return POPPLER_STRUCTURE_ELEMENT_NONSTRUCT;
      case StructElement::TOC:
        return POPPLER_STRUCTURE_ELEMENT_TOC;
      case StructElement::TOCI:
        return POPPLER_STRUCTURE_ELEMENT_TOC_ITEM;
      case StructElement::Index:
        return POPPLER_STRUCTURE_ELEMENT_INDEX;
      case StructElement::Private:
        return POPPLER_STRUCTURE_ELEMENT_PRIVATE;
      case StructElement::P:
        return POPPLER_STRUCTURE_ELEMENT_PARAGRAPH;
      case StructElement::H:
        return POPPLER_STRUCTURE_ELEMENT_HEADING;
      case StructElement::H1:
        return POPPLER_STRUCTURE_ELEMENT_HEADING_1;
      case StructElement::H2:
        return POPPLER_STRUCTURE_ELEMENT_HEADING_2;
      case StructElement::H3:
        return POPPLER_STRUCTURE_ELEMENT_HEADING_3;
      case StructElement::H4:
        return POPPLER_STRUCTURE_ELEMENT_HEADING_4;
      case StructElement::H5:
        return POPPLER_STRUCTURE_ELEMENT_HEADING_5;
      case StructElement::H6:
        return POPPLER_STRUCTURE_ELEMENT_HEADING_6;
      case StructElement::L:
        return POPPLER_STRUCTURE_ELEMENT_LIST;
      case StructElement::LI:
        return POPPLER_STRUCTURE_ELEMENT_LIST_ITEM;
      case StructElement::Lbl:
        return POPPLER_STRUCTURE_ELEMENT_LIST_LABEL;
      case StructElement::LBody:
        return POPPLER_STRUCTURE_ELEMENT_LIST_BODY;
      case StructElement::Table:
        return POPPLER_STRUCTURE_ELEMENT_TABLE;
      case StructElement::TR:
        return POPPLER_STRUCTURE_ELEMENT_TABLE_ROW;
      case StructElement::TH:
        return POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING;
      case StructElement::TD:
        return POPPLER_STRUCTURE_ELEMENT_TABLE_DATA;
      case StructElement::THead:
        return POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER;
      case StructElement::TFoot:
        return POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER;
      case StructElement::TBody:
        return POPPLER_STRUCTURE_ELEMENT_TABLE_BODY;
      case StructElement::Ruby:
        return POPPLER_STRUCTURE_ELEMENT_RUBY;
      case StructElement::RB:
        return POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT;
      case StructElement::RT:
        return POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT;
      case StructElement::RP:
        return POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION;
      case StructElement::Warichu:
        return POPPLER_STRUCTURE_ELEMENT_WARICHU;
      case StructElement::WT:
        return POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT;
      case StructElement::WP:
        return POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION;
      case StructElement::Figure:
        return POPPLER_STRUCTURE_ELEMENT_FIGURE;
      case StructElement::Formula:
        return POPPLER_STRUCTURE_ELEMENT_FORMULA;
      case StructElement::Form:
        return POPPLER_STRUCTURE_ELEMENT_FORM;

      /* There should never be elements of type StructElement::Unknown */
      case StructElement::Unknown:
        g_assert_not_reached ();
    }

  g_assert_not_reached ();
  return POPPLER_STRUCTURE_ELEMENT_CONTENT;
}


template <typename EnumType>
struct EnumNameValue {
  const gchar *name;
  EnumType     value;

  static const EnumNameValue<EnumType> values[];
  static const Attribute::Type attribute_type;
};

#define ENUM_VALUES(E, A) \
  template<> const Attribute::Type EnumNameValue<E>::attribute_type = Attribute::A; \
  template<> const EnumNameValue<E> EnumNameValue<E>::values[] =

ENUM_VALUES (PopplerStructurePlacement, Placement)
{
  { "Block",  POPPLER_STRUCTURE_PLACEMENT_BLOCK  },
  { "Inline", POPPLER_STRUCTURE_PLACEMENT_INLINE },
  { "Before", POPPLER_STRUCTURE_PLACEMENT_BEFORE },
  { "Start",  POPPLER_STRUCTURE_PLACEMENT_START  },
  { "End",    POPPLER_STRUCTURE_PLACEMENT_END    },
  { NULL }
};

ENUM_VALUES (PopplerStructureWritingMode, WritingMode)
{
  { "LrTb", POPPLER_STRUCTURE_WRITING_MODE_LR_TB },
  { "RlTb", POPPLER_STRUCTURE_WRITING_MODE_RL_TB },
  { "TbRl", POPPLER_STRUCTURE_WRITING_MODE_TB_RL },
  { NULL }
};

ENUM_VALUES (PopplerStructureBorderStyle, BorderStyle)
{
  { "None",   POPPLER_STRUCTURE_BORDER_STYLE_NONE   },
  { "Hidden", POPPLER_STRUCTURE_BORDER_STYLE_HIDDEN },
  { "Dotted", POPPLER_STRUCTURE_BORDER_STYLE_DOTTED },
  { "Dashed", POPPLER_STRUCTURE_BORDER_STYLE_DASHED },
  { "Solid",  POPPLER_STRUCTURE_BORDER_STYLE_SOLID  },
  { "Double", POPPLER_STRUCTURE_BORDER_STYLE_DOUBLE },
  { "Groove", POPPLER_STRUCTURE_BORDER_STYLE_GROOVE },
  { "Inset",  POPPLER_STRUCTURE_BORDER_STYLE_INSET  },
  { "Outset", POPPLER_STRUCTURE_BORDER_STYLE_OUTSET },
  { NULL }
};

ENUM_VALUES (PopplerStructureTextAlign, TextAlign)
{
  { "Start",   POPPLER_STRUCTURE_TEXT_ALIGN_START   },
  { "Center",  POPPLER_STRUCTURE_TEXT_ALIGN_CENTER  },
  { "End",     POPPLER_STRUCTURE_TEXT_ALIGN_END     },
  { "Justify", POPPLER_STRUCTURE_TEXT_ALIGN_JUSTIFY },
  { NULL }
};

ENUM_VALUES (PopplerStructureBlockAlign, BlockAlign)
{
  { "Before",  POPPLER_STRUCTURE_BLOCK_ALIGN_BEFORE  },
  { "Middle",  POPPLER_STRUCTURE_BLOCK_ALIGN_MIDDLE  },
  { "After",   POPPLER_STRUCTURE_BLOCK_ALIGN_AFTER   },
  { "Justify", POPPLER_STRUCTURE_BLOCK_ALIGN_JUSTIFY },
  { NULL }
};

ENUM_VALUES (PopplerStructureInlineAlign, InlineAlign)
{
  { "Start",  POPPLER_STRUCTURE_INLINE_ALIGN_START  },
  { "Center", POPPLER_STRUCTURE_INLINE_ALIGN_CENTER },
  { "End",    POPPLER_STRUCTURE_INLINE_ALIGN_END    },
  { NULL }
};

ENUM_VALUES (PopplerStructureTextDecoration, TextDecorationType)
{
  { "None",        POPPLER_STRUCTURE_TEXT_DECORATION_NONE        },
  { "Underline",   POPPLER_STRUCTURE_TEXT_DECORATION_UNDERLINE   },
  { "Overline",    POPPLER_STRUCTURE_TEXT_DECORATION_OVERLINE    },
  { "LineThrough", POPPLER_STRUCTURE_TEXT_DECORATION_LINETHROUGH },
  { NULL }
};

ENUM_VALUES (PopplerStructureRubyAlign, RubyAlign)
{
  { "Start",      POPPLER_STRUCTURE_RUBY_ALIGN_START      },
  { "Center",     POPPLER_STRUCTURE_RUBY_ALIGN_CENTER     },
  { "End",        POPPLER_STRUCTURE_RUBY_ALIGN_END        },
  { "Justify",    POPPLER_STRUCTURE_RUBY_ALIGN_JUSTIFY    },
  { "Distribute", POPPLER_STRUCTURE_RUBY_ALIGN_DISTRIBUTE },
  { NULL }
};

ENUM_VALUES (PopplerStructureRubyPosition, RubyPosition)
{
  { "Before",  POPPLER_STRUCTURE_RUBY_POSITION_BEFORE  },
  { "After",   POPPLER_STRUCTURE_RUBY_POSITION_AFTER   },
  { "Warichu", POPPLER_STRUCTURE_RUBY_POSITION_WARICHU },
  { "Inline",  POPPLER_STRUCTURE_RUBY_POSITION_INLINE  },
  { NULL }
};

ENUM_VALUES (PopplerStructureGlyphOrientation, GlyphOrientationVertical)
{
  { "Auto", POPPLER_STRUCTURE_GLYPH_ORIENTATION_AUTO },
  { "90",   POPPLER_STRUCTURE_GLYPH_ORIENTATION_90   },
  { "180",  POPPLER_STRUCTURE_GLYPH_ORIENTATION_180  },
  { "270",  POPPLER_STRUCTURE_GLYPH_ORIENTATION_270  },
  { "360",  POPPLER_STRUCTURE_GLYPH_ORIENTATION_0    },
  { "-90",  POPPLER_STRUCTURE_GLYPH_ORIENTATION_270  },
  { "-180", POPPLER_STRUCTURE_GLYPH_ORIENTATION_180  },
  { NULL }
};

ENUM_VALUES (PopplerStructureListNumbering, ListNumbering)
{
  { "None",       POPPLER_STRUCTURE_LIST_NUMBERING_NONE        },
  { "Disc",       POPPLER_STRUCTURE_LIST_NUMBERING_DISC        },
  { "Circle",     POPPLER_STRUCTURE_LIST_NUMBERING_CIRCLE      },
  { "Square",     POPPLER_STRUCTURE_LIST_NUMBERING_SQUARE      },
  { "Decimal",    POPPLER_STRUCTURE_LIST_NUMBERING_DECIMAL     },
  { "UpperRoman", POPPLER_STRUCTURE_LIST_NUMBERING_UPPER_ROMAN },
  { "LowerRoman", POPPLER_STRUCTURE_LIST_NUMBERING_LOWER_ROMAN },
  { "UpperAlpha", POPPLER_STRUCTURE_LIST_NUMBERING_UPPER_ALPHA },
  { "LowerAlpha", POPPLER_STRUCTURE_LIST_NUMBERING_LOWER_ALPHA },
  { NULL }
};

ENUM_VALUES (PopplerStructureFormRole, Role)
{
  { "rb", POPPLER_STRUCTURE_FORM_ROLE_RADIO_BUTTON },
  { "cb", POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX     },
  { "pb", POPPLER_STRUCTURE_FORM_ROLE_PUSH_BUTTON  },
  { "tv", POPPLER_STRUCTURE_FORM_ROLE_TEXT_VALUE   },
  { NULL }
};

ENUM_VALUES (PopplerStructureFormState, checked)
{
  { "on",      POPPLER_STRUCTURE_FORM_STATE_ON      },
  { "off",     POPPLER_STRUCTURE_FORM_STATE_OFF     },
  { "neutral", POPPLER_STRUCTURE_FORM_STATE_NEUTRAL },
  { NULL }
};

ENUM_VALUES (PopplerStructureTableScope, Scope)
{
  { "Row",    POPPLER_STRUCTURE_TABLE_SCOPE_ROW    },
  { "Column", POPPLER_STRUCTURE_TABLE_SCOPE_COLUMN },
  { "Both",   POPPLER_STRUCTURE_TABLE_SCOPE_BOTH   },
  { NULL }
};

#undef ENUM_VALUES


template <typename EnumType>
static EnumType
name_to_enum (Object *name_value)
{
  /*
   * Non-NULL names must always be valid because Poppler
   * discards the invalid attributes when parsing them.
   */
  g_assert (name_value != NULL);

  for (const EnumNameValue<EnumType> *item = EnumNameValue<EnumType>::values ; item->name; item++)
    if (name_value->isName (item->name))
      return item->value;

  g_assert_not_reached ();
  return static_cast<EnumType> (-1);
}


template <typename EnumType>
static EnumType
attr_to_enum (PopplerStructureElement *poppler_structure_element)
{
  const Attribute *attr =
      poppler_structure_element->elem->findAttribute (EnumNameValue<EnumType>::attribute_type, gTrue);
  return name_to_enum<EnumType> ((attr != NULL)
                                 ? attr->getValue ()
                                 : Attribute::getDefaultValue (EnumNameValue<EnumType>::attribute_type));
}


static inline Object *
attr_value_or_default (PopplerStructureElement *poppler_structure_element,
                       Attribute::Type          attribute_type)
{
  const Attribute *attr =
      poppler_structure_element->elem->findAttribute (attribute_type, gTrue);
  return attr ? attr->getValue () : Attribute::getDefaultValue (attribute_type);
}


/**
 * poppler_structure_element_get_page:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the page number in which the element is contained.
 *
 * Return value: Number of the page that contains the element, of
 *    <code>-1</code> if not defined.
 *
 * Since: 0.26
 */
gint
poppler_structure_element_get_page (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), -1);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, -1);

  Ref ref;
  if (poppler_structure_element->elem->getPageRef (ref))
    {
      return poppler_structure_element->document->doc->findPage(ref.num, ref.gen) - 1;
    }

  return -1;
}

/**
 * poppler_structure_element_is_content:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Checks whether an element is actual document content.
 *
 * Return value: %TRUE if the element is content, or %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_is_content (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, FALSE);

  return poppler_structure_element->elem->isContent ();
}

/**
 * poppler_structure_element_is_inline:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Checks whether an element is an inline element.
 *
 * Return value: %TRUE if the element is an inline element, or %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_is_inline (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, FALSE);

  return poppler_structure_element->elem->isInline ();
}

/**
 * poppler_structure_element_is_block:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Checks whether an element is a block element.
 *
 * Return value: %TRUE if  the element is a block element, or %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_is_block (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, FALSE);

  return poppler_structure_element->elem->isBlock ();
}

/**
 * poppler_structure_element_is_grouping:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Checks whether an element is a grouping element.
 *
 * Return value: %TRUE if the element is a grouping element, %FALSE
 *    otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_is_grouping (PopplerStructureElement *poppler_structure_element)
{
    g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
    g_return_val_if_fail (poppler_structure_element->elem != NULL, FALSE);

    return poppler_structure_element->elem->isGrouping ();
}

/**
 * poppler_structure_element_get_id:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the identifier of an element.
 *
 * Return value: (transfer full): The identifier of the element (if
 *    defined), or %NULL.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_id (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  GooString *string = poppler_structure_element->elem->getID ();
  return string ? _poppler_goo_string_to_utf8 (string) : NULL;
}

/**
 * poppler_structure_element_get_title:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the title of an element.
 *
 * Return value: (transfer full): The title of the element, or %NULL.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_title (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  GooString *string = poppler_structure_element->elem->getTitle ();
  return string ? _poppler_goo_string_to_utf8 (string) : NULL;
}

/**
 * popppler_structure_element_get_abbreviation:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Acronyms and abbreviations contained in elements of type
 * #POPPLER_STRUCTURE_ELEMENT_SPAN may have an associated expanded
 * text form, which can be retrieved using this function.
 *
 * Return value: (transfer full): Text of the expanded abbreviation if the
 *    element text is an abbreviation or acrony, %NULL if not.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_abbreviation (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  if (poppler_structure_element->elem->getType () != StructElement::Span)
    return NULL;

  GooString *string = poppler_structure_element->elem->getExpandedAbbr ();
  return string ? _poppler_goo_string_to_utf8 (string) : NULL;
}

/**
 * poppler_structure_element_get_language:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the language and country code for the content in an element,
 * in two-letter ISO format, e.g. <code>en_ES</code>, or %NULL if not
 * defined.
 *
 * Return value: (transfer full): language and country code, or %NULL.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_language (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  GooString *string = poppler_structure_element->elem->getLanguage ();
  return string ? _poppler_goo_string_to_utf8 (string) : NULL;
}

/**
 * poppler_structure_element_get_alt_text:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the “alternate” text representation of the element (and its child
 * elements). This is mostly used for non-text elements like images and
 * figures, to specify a textual description of the element.
 *
 * Note that for elements containing proper text, the function
 * poppler_structure_element_get_text() must be used instead.
 *
 * Return value: (transfer full): The alternate text representation for the
 *    element, or %NULL if not defined.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_alt_text (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  GooString *string = poppler_structure_element->elem->getAltText ();
  return string ? _poppler_goo_string_to_utf8 (string) : NULL;
}

/**
 * poppler_structure_element_get_actual_text:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the actual text enclosed by the element (and its child elements).
 * The actual text is mostly used for non-text elements like images and
 * figures which <emphasis>do</emphasis> have the graphical appearance of text, like
 * a logo. For those the actual text is the equivalent text to those
 * graphical elements which look like text when rendered.
 *
 * Note that for elements containing proper text, the function
 * poppler_structure_element_get_text() must be used instead.
 *
 * Return value: (transfer full): The actual text for the element, or %NULL
 *    if not defined.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_actual_text (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  GooString *string = poppler_structure_element->elem->getActualText ();
  return string ? _poppler_goo_string_to_utf8 (string) : NULL;
}

/**
 * poppler_structure_element_get_text:
 * @poppler_structure_element: A #PopplerStructureElement
 * @flags: A #PopplerStructureGetTextFlags value, or
 *    %POPPLER_STRUCTURE_GET_TEXT_NONE to disable all the flags.
 *
 * Obtains the text enclosed by an element, or the text enclosed by the
 * elements in the subtree (including the element itself).
 *
 * Return value: (transfer full): A string.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_text (PopplerStructureElement     *poppler_structure_element,
                                    PopplerStructureGetTextFlags flags)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);


  GooString *string =
      poppler_structure_element->elem->getText (flags & POPPLER_STRUCTURE_GET_TEXT_RECURSIVE);
  gchar *result = string ? _poppler_goo_string_to_utf8 (string) : NULL;
  delete string;
  return result;
}

struct _PopplerStructureElementIter
{
  PopplerDocument *document;
  union {
    StructElement  *elem;
    StructTreeRoot *root;
  };
  gboolean is_root;
  unsigned index;
};

POPPLER_DEFINE_BOXED_TYPE (PopplerStructureElementIter,
                           poppler_structure_element_iter,
                           poppler_structure_element_iter_copy,
                           poppler_structure_element_iter_free)

/**
 * poppler_structure_element_iter_copy:
 * @iter: a #PopplerStructureElementIter
 *
 * Creates a new #PopplerStructureElementIter as a copy of @iter. The
 * returned value must be freed with poppler_structure_element_iter_free().
 *
 * Return value: (transfer full): a new #PopplerStructureElementIter
 *
 * Since: 0.26
 */
PopplerStructureElementIter *
poppler_structure_element_iter_copy (PopplerStructureElementIter *iter)
{
  PopplerStructureElementIter *new_iter;

  g_return_val_if_fail (iter != NULL, NULL);

  new_iter = g_slice_dup (PopplerStructureElementIter, iter);
  new_iter->document = (PopplerDocument *) g_object_ref (new_iter->document);

  return new_iter;
}

/**
 * poppler_structure_element_iter_free:
 * @iter: a #PopplerStructureElementIter
 *
 * Frees @iter.
 *
 * Since: 0.26
 */
void
poppler_structure_element_iter_free (PopplerStructureElementIter *iter)
{
  if (G_UNLIKELY (iter == NULL))
    return;

  g_object_unref (iter->document);
  g_slice_free (PopplerStructureElementIter, iter);
}

/**
 * poppler_structure_element_iter_new:
 * @poppler_document: a #PopplerDocument.
 *
 * Returns the root #PopplerStructureElementIter for @document, or %NULL. The
 * returned value must be freed with poppler_structure_element_iter_free().
 *
 * Documents may have an associated structure tree &mdashmostly, Tagged-PDF
 * compliant documents&mdash; which can be used to obtain information about
 * the document structure and its contents. Each node in the tree contains
 * a #PopplerStructureElement.
 *
 * Here is a simple example that walks the whole tree:
 *
 * <informalexample><programlisting>
 * static void
 * walk_structure (PopplerStructureElementIter *iter)
 * {
 *   do {
 *     /<!-- -->* Get the element and do something with it *<!-- -->/
 *     PopplerStructureElementIter *child = poppler_structure_element_iter_get_child (iter);
 *     if (child)
 *       walk_structure (child);
 *     poppler_structure_element_iter_free (child);
 *   } while (poppler_structure_element_iter_next (iter));
 * }
 * ...
 * {
 *   iter = poppler_structure_element_iter_new (document);
 *   walk_structure (iter);
 *   poppler_structure_element_iter_free (iter);
 * }
 * </programlisting></informalexample>
 *
 * Return value: (transfer full): a new #PopplerStructureElementIter, or %NULL if document
 *    doesn't have structure tree.
 *
 * Since: 0.26
 */
PopplerStructureElementIter *
poppler_structure_element_iter_new (PopplerDocument *poppler_document)
{
  PopplerStructureElementIter *iter;
  StructTreeRoot *root;

  g_return_val_if_fail (POPPLER_IS_DOCUMENT (poppler_document), NULL);

  root = poppler_document->doc->getStructTreeRoot ();
  if (root == NULL)
    return NULL;

  if (root->getNumChildren () == 0)
    return NULL;

  iter = g_slice_new0 (PopplerStructureElementIter);
  iter->document = (PopplerDocument *) g_object_ref (poppler_document);
  iter->is_root = TRUE;
  iter->root = root;

  return iter;
}

/**
 * poppler_structure_element_iter_next:
 * @iter: a #PopplerStructureElementIter
 *
 * Sets @iter to point to the next structure element at the current level
 * of the tree, if valid. See poppler_structure_element_iter_new() for more
 * information.
 *
 * Return value: %TRUE, if @iter was set to the next structure element
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_iter_next (PopplerStructureElementIter *iter)
{
  unsigned elements;

  g_return_val_if_fail (iter != NULL, FALSE);

  elements = iter->is_root
    ? iter->root->getNumChildren ()
    : iter->elem->getNumChildren ();

  return ++iter->index < elements;
}

/**
 * poppler_structure_element_iter_get_element:
 * @iter: a #PopplerStructureElementIter
 *
 * Returns the #PopplerStructureElementIter associated with @iter.
 *
 * Return value: (transfer full): a new #PopplerStructureElementIter
 *
 * Since: 0.26
 */
PopplerStructureElement *
poppler_structure_element_iter_get_element (PopplerStructureElementIter *iter)
{
  StructElement *elem;

  g_return_val_if_fail (iter != NULL, NULL);

  elem = iter->is_root
    ? iter->root->getChild (iter->index)
    : iter->elem->getChild (iter->index);

  return _poppler_structure_element_new (iter->document, elem);
}

/**
 * poppler_structure_element_iter_get_child:
 * @parent: a #PopplerStructureElementIter
 *
 * Returns a new iterator to the children elements of the
 * #PopplerStructureElement associated with @iter. The returned value must
 * be freed with poppler_structure_element_iter_free().
 *
 * Return value: a new #PopplerStructureElementIter
 *
 * Since: 0.26
 */
PopplerStructureElementIter *
poppler_structure_element_iter_get_child (PopplerStructureElementIter *parent)
{
  StructElement *elem;

  g_return_val_if_fail (parent != NULL, NULL);

  elem = parent->is_root
    ? parent->root->getChild (parent->index)
    : parent->elem->getChild (parent->index);

  if (elem->getNumChildren () > 0)
    {
      PopplerStructureElementIter *child = g_slice_new0 (PopplerStructureElementIter);
      child->document = (PopplerDocument *) g_object_ref (parent->document);
      child->elem = elem;
      return child;
    }

  return NULL;
}


struct _PopplerTextSpan {
  gchar *text;
  gchar *font_name;
  guint  flags;
  PopplerColor color;
};

POPPLER_DEFINE_BOXED_TYPE (PopplerTextSpan,
                           poppler_text_span,
                           poppler_text_span_copy,
                           poppler_text_span_free)

enum {
  POPPLER_TEXT_SPAN_FIXED_WIDTH = (1 << 0),
  POPPLER_TEXT_SPAN_SERIF       = (1 << 1),
  POPPLER_TEXT_SPAN_ITALIC      = (1 << 2),
  POPPLER_TEXT_SPAN_BOLD        = (1 << 3),
};

static PopplerTextSpan *
text_span_poppler_text_span (const TextSpan& span)
{
    PopplerTextSpan *new_span = g_slice_new0 (PopplerTextSpan);
    if (GooString *text = span.getText ())
      new_span->text = _poppler_goo_string_to_utf8 (text);

    new_span->color.red = colToDbl (span.getColor ().r) * 65535;
    new_span->color.green = colToDbl (span.getColor ().g) * 65535;
    new_span->color.blue = colToDbl (span.getColor ().b) * 65535;

    if (span.getFont ())
      {
        // GfxFont sometimes does not have a family name but there
        // is always a font name that can be used as fallback.
        GooString *font_name = span.getFont ()->getFamily ();
        if (font_name == NULL)
          font_name = span.getFont ()->getName ();

        new_span->font_name = _poppler_goo_string_to_utf8 (font_name);
        if (span.getFont ()->isFixedWidth ())
          new_span->flags |= POPPLER_TEXT_SPAN_FIXED_WIDTH;
        if (span.getFont ()->isSerif ())
            new_span->flags |= POPPLER_TEXT_SPAN_SERIF;
        if (span.getFont ()->isItalic ())
            new_span->flags |= POPPLER_TEXT_SPAN_ITALIC;
        if (span.getFont ()->isBold ())
            new_span->flags |= POPPLER_TEXT_SPAN_BOLD;

        /* isBold() can return false for some fonts whose weight is heavy */
        switch (span.getFont ()->getWeight ())
          {
          case GfxFont::W500:
          case GfxFont::W600:
          case GfxFont::W700:
          case GfxFont::W800:
          case GfxFont::W900:
            new_span->flags |= POPPLER_TEXT_SPAN_BOLD;
          default:
            break;
          }
      }

    return new_span;
}

/**
 * poppler_text_span_copy:
 * @poppler_text_span: a #PopplerTextSpan
 *
 * Makes a copy of a text span.
 *
 * Return value: (transfer full): A new #PopplerTextSpan
 *
 * Since: 0.26
 */
PopplerTextSpan *
poppler_text_span_copy (PopplerTextSpan *poppler_text_span)
{
  PopplerTextSpan *new_span;

  g_return_val_if_fail (poppler_text_span != NULL, NULL);

  new_span = g_slice_dup (PopplerTextSpan, poppler_text_span);
  new_span->text = g_strdup (poppler_text_span->text);
  if (poppler_text_span->font_name)
    new_span->font_name = g_strdup (poppler_text_span->font_name);
  return new_span;
}

/**
 * poppler_text_span_free:
 * @poppler_text_span: A #PopplerTextSpan
 *
 * Frees a text span.
 *
 * Since: 0.26
 */
void
poppler_text_span_free (PopplerTextSpan *poppler_text_span)
{
  if (G_UNLIKELY (poppler_text_span == NULL))
    return;

  g_free (poppler_text_span->text);
  g_free (poppler_text_span->font_name);
  g_slice_free (PopplerTextSpan, poppler_text_span);
}

/**
 * poppler_text_span_is_fixed_width_font:
 * @poppler_text_span: a #PopplerTextSpan
 *
 * Check wether a text span is meant to be rendered using a fixed-width font.
 *
 * Return value: Whether the span uses a fixed-width font.
 *
 * Since: 0.26
 */
gboolean
poppler_text_span_is_fixed_width_font (PopplerTextSpan *poppler_text_span)
{
  g_return_val_if_fail (poppler_text_span != NULL, FALSE);

  return (poppler_text_span->flags & POPPLER_TEXT_SPAN_FIXED_WIDTH);
}

/**
 * poppler_text_span_is_serif_font:
 * @poppler_text_span: a #PopplerTextSpan
 *
 * Check whether a text span is meant to be rendered using a serif font.
 *
 * Return value: Whether the span uses a serif font.
 *
 * Since: 0.26
 */
gboolean
poppler_text_span_is_serif_font (PopplerTextSpan *poppler_text_span)
{
  g_return_val_if_fail (poppler_text_span != NULL, FALSE);

  return (poppler_text_span->flags & POPPLER_TEXT_SPAN_SERIF);
}

/**
 * poppler_text_span_is_bold_font:
 * @poppler_text_span: a #PopplerTextSpan
 *
 * Check whether a text span is meant to be rendered using a bold font.
 *
 * Return value: Whether the span uses bold font.
 *
 * Since: 0.26
 */
gboolean
poppler_text_span_is_bold_font (PopplerTextSpan *poppler_text_span)
{
  g_return_val_if_fail (poppler_text_span != NULL, FALSE);

  return (poppler_text_span->flags & POPPLER_TEXT_SPAN_BOLD);
}

/**
 * poppler_text_span_get_color:
 * @poppler_text_span: a #PopplerTextSpan
 * @color: (out): a return location for a #PopplerColor
 *
 * Obtains the color in which the text is to be rendered.
 *
 * Since: 0.26
 */
void
poppler_text_span_get_color (PopplerTextSpan *poppler_text_span,
                             PopplerColor *color)
{
  g_return_if_fail (poppler_text_span != NULL);
  g_return_if_fail (color != NULL);

  *color = poppler_text_span->color;
}

/**
 * poppler_text_span_get_text:
 * @poppler_text_span: a #PopplerTextSpan
 *
 * Obtains the text contained in the span.
 *
 * Return value: (transfer none): A string.
 *
 * Since: 0.26
 */
const gchar *
poppler_text_span_get_text (PopplerTextSpan *poppler_text_span)
{
  g_return_val_if_fail (poppler_text_span != NULL, NULL);

  return poppler_text_span->text;
}

/**
 * poppler_text_span_get_font_name:
 * @poppler_text_span: a #PopplerTextSpan
 *
 * Obtains the name of the font in which the span is to be rendered.
 *
 * Return value: (transfer none): A string containing the font name, or
 *   %NULL if a font is not defined.
 *
 * Since: 0.26
 */
const gchar *
poppler_text_span_get_font_name (PopplerTextSpan *poppler_text_span)
{
  g_return_val_if_fail (poppler_text_span != NULL, NULL);

  return poppler_text_span->font_name;
}

/**
 * poppler_structure_element_get_text_spans:
 * @poppler_structure_element: A #PopplerStructureElement
 * @n_text_spans: (out): A pointer to the location where the number of elements in
 *    the returned array will be stored.
 *
 * Obtains the text enclosed by an element, as an array of #PopplerTextSpan
 * structures. Each item in the list is a piece of text which share the same
 * attributes, plus its attributes. The following example shows how to
 * obtain and free the text spans of an element:
 *
 * <informalexample><programlisting>
 * guint i, n_spans;
 * PopplerTextSpan **text_spans =
 *    poppler_structure_element_get_text_spans (element, &n_spans);
 * /<!-- -->* Use the text spans *<!-- -->/
 * for (i = 0; i < n_spans; i++)
 *    poppler_text_span_free (text_spans[i]);
 * g_free (text_spans);
 * </programlisting></informalexample>
 *
 * Return value: (transfer full) (array length=n_text_spans) (element-type PopplerTextSpan):
 *    An array of #PopplerTextSpan elments.
 *
 * Since: 0.26
 */
PopplerTextSpan **
poppler_structure_element_get_text_spans (PopplerStructureElement *poppler_structure_element,
                                          guint                   *n_text_spans)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);
  g_return_val_if_fail (n_text_spans != NULL, NULL);
  g_return_val_if_fail (poppler_structure_element->elem != NULL, NULL);

  if (!poppler_structure_element->elem->isContent ())
    return NULL;

  const TextSpanArray spans(poppler_structure_element->elem->getTextSpans ());
  PopplerTextSpan **text_spans = g_new0 (PopplerTextSpan*, spans.size ());

  size_t i = 0;
  for (TextSpanArray::const_iterator s = spans.begin (); s != spans.end (); ++s)
    text_spans[i++] = text_span_poppler_text_span (*s);

  *n_text_spans = spans.size ();

  return text_spans;
}

/* General Layout Attributes */

/**
 * poppler_structure_element_get_placement:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the placement type of the structure element.
 *
 * Return value: A #PopplerStructurePlacement value.
 *
 * Since: 0.26
 */
PopplerStructurePlacement
poppler_structure_element_get_placement (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element),
                        EnumNameValue<PopplerStructurePlacement>::values[0].value);
  return attr_to_enum<PopplerStructurePlacement> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_writing_mode:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the writing mode (writing direction) of the content associated
 * with a structure element.
 *
 * Return value: A #PopplerStructureWritingMode value.
 *
 * Since: 0.26
 */
PopplerStructureWritingMode
poppler_structure_element_get_writing_mode (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element),
                        EnumNameValue<PopplerStructureWritingMode>::values[0].value);
  return attr_to_enum<PopplerStructureWritingMode> (poppler_structure_element);
}


static void
convert_border_style (Object *object, PopplerStructureBorderStyle *values)
{
  g_assert (object != NULL);
  g_assert (values != NULL);

  if (object->isArray ())
    {
      g_assert (object->arrayGetLength () == 4);
      for (guint i = 0; i < 4; i++)
        {
          Object item;
          values[i] = name_to_enum<PopplerStructureBorderStyle> (object->arrayGet (i, &item));
          item.free ();
        }
    }
  else
    {
      values[0] = values[1] = values[2] = values[3] =
        name_to_enum<PopplerStructureBorderStyle> (object);
    }
}

/**
 * poppler_structure_element_get_border_style:
 * @poppler_structure_element: A #PopplerStructureElement
 * @border_styles: (out) (array fixed-size=4) (element-type PopplerStructureBorderStyle):
 *    An array of four #PopplerStructureBorderStyle elements.
 *
 * Obtains the border style of a structure element. The result values
 * are in before-after-start-end ordering. For example, using Western
 * left-to-right writing, that is top-bottom-left-right.
 *
 * Since: 0.26
 */
void
poppler_structure_element_get_border_style (PopplerStructureElement     *poppler_structure_element,
                                            PopplerStructureBorderStyle *border_styles)
{
  g_return_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element));
  g_return_if_fail (border_styles != NULL);

  convert_border_style (attr_value_or_default (poppler_structure_element,
                                               Attribute::BorderStyle),
                        border_styles);
}

static inline void
convert_doubles_array (Object *object, gdouble **values, guint *n_values)
{
  g_assert (object->isArray ());
  g_assert (n_values != NULL);
  g_assert (values != NULL);

  *n_values = object->arrayGetLength ();
  gdouble* doubles = g_new (gdouble, *n_values);

  for (guint i = 0; i < *n_values; i++)
    {
      Object item;
      doubles[i] = object->arrayGet (i, &item)->getNum ();
      item.free ();
    }
}

static inline void
convert_color (Object *object, PopplerColor *color)
{
  g_assert (color != NULL);
  g_assert (object->isArray () && object->arrayGetLength () != 3);

  Object item;

  color->red = object->arrayGet (0, &item)->getNum () * 65535;
  item.free ();

  color->green = object->arrayGet (1, &item)->getNum () * 65535;
  item.free ();

  color->blue = object->arrayGet (2, &item)->getNum () * 65535;
  item.free ();
}

/**
 * poppler_structure_element_get_color:
 * @poppler_structure_element: A #PopplerStructureElement
 * @color: (out): A #PopplerColor.
 *
 * Obtains the color of the content contained in the element.
 * If this attribute is not specified, the color for this element shall
 * be the current text fill color in effect at the start of its associated content.
 *
 * Return value: %TRUE if a color is defined for the element,
 *    %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_get_color (PopplerStructureElement *poppler_structure_element,
                                     PopplerColor            *color)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (color != NULL, FALSE);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Color);
  if (value == NULL)
    return FALSE;

  convert_color (value, color);
  return TRUE;
}

/**
 * poppler_structure_element_get_background_color:
 * @poppler_structure_element: A #PopplerStructureElement
 * @color: (out): A #PopplerColor.
 *
 * Obtains the background color of the element. If this attribute is
 * not specified, the element shall be treated as if it were transparent.
 *
 * Return value: %TRUE if a color is defined for the element,
 *    %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_get_background_color (PopplerStructureElement *poppler_structure_element,
                                                PopplerColor            *color)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (color != NULL, FALSE);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::BackgroundColor);
  if (value == NULL)
    return FALSE;

  convert_color (value, color);
  return TRUE;
}

/**
 * poppler_structure_element_get_border_color:
 * @poppler_structure_element: A #PopplerStructureElement
 * @colors: (out) (array fixed-size=4) (element-type PopplerColor): An array
 *    of four #PopplerColor.
 *
 * Obtains the color of border around the element. The result values
 * are in before-after-start-end ordering (for the typical Western
 * left-to-right writing, that is top-bottom-left-right).
 * If this attribute is not specified, the border color for this element shall
 * be the current text fill color in effect at the start of its associated
 * content.
 *
 * Return value: %TRUE if a color is defined for the element,
 *    %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_get_border_color (PopplerStructureElement *poppler_structure_element,
                                            PopplerColor            *colors)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (colors != NULL, FALSE);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::BorderColor);
  if (value == NULL)
    return FALSE;

  g_assert (value->isArray ());
  if (value->arrayGetLength () == 4)
    {
      // One color per side.
      for (guint i = 0; i < 4; i++)
        {
          Object item;
          convert_color (value->arrayGet (i, &item), &colors[i]);
          item.free ();
        }
    }
  else
    {
      // Same color in all sides.
      g_assert (value->arrayGetLength () == 3);
      convert_color (value, &colors[0]);
      colors[1] = colors[2] = colors[3] = colors[0];
    }

  return TRUE;
}

static inline void
convert_double_or_4_doubles (Object *object, gdouble *value)
{
  g_assert (object != NULL);

  if (object->isArray ())
    {
      g_assert (object->arrayGetLength () == 4);
      for (guint i = 0; i < 4; i++)
        {
          Object item;
          value[i] = object->arrayGet (i, &item)->getNum ();
          item.free ();
        }
    }
  else
    {
      g_assert (object->isNum ());
      value[0] = value[1] = value[2] = value[3] = object->getNum ();
    }
}

/**
 * poppler_structure_element_get_border_thickness:
 * @poppler_structure_element: A #PopplerStructureElement
 * @border_thicknesses: (out) (array fixed-size=4) (element-type gdouble):
 *    Array with the four values of border thicknesses.
 *
 * Obtains the thickness of the border of an element. The result values
 * are in before-after-start-end ordering (for the typical Western
 * left-to-right writing, that is top-bottom-left-right).
 * A value of 0 indicates that the border shall not be drawn.
 *
 * Return value: %TRUE if the border thickness attribute is defined for
 *    the element, %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_get_border_thickness (PopplerStructureElement *poppler_structure_element,
                                                gdouble                 *border_thicknesses)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), FALSE);
  g_return_val_if_fail (border_thicknesses != NULL, FALSE);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::BorderThickness);
  if (value == NULL)
    return FALSE;

  convert_double_or_4_doubles (value, border_thicknesses);
  return TRUE;
}

/**
 * poppler_structure_element_get_padding:
 * @poppler_structure_element: A #PopplerStructureElement
 * @paddings: (out) (array fixed-size=4) (element-type gdouble):
 *    Padding for the four sides of the element.
 *
 * Obtains the padding of an element (space around it). The result
 * values are in before-after-start-end ordering. For example using
 * Western left-to-right writing, that is top-bottom-left-right.
 *
 * Since: 0.26
 */
void
poppler_structure_element_get_padding (PopplerStructureElement *poppler_structure_element,
                                       gdouble                 *paddings)
{
  g_return_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element));
  g_return_if_fail (paddings != NULL);

  convert_double_or_4_doubles (attr_value_or_default (poppler_structure_element,
                                                      Attribute::Padding),
                               paddings);
}

/* Layout Attributes for block-level structure elements */

/**
 * poppler_structure_element_get_space_before:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the amount of empty space before the block-level structure element.
 *
 * Return value: A positive value.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_space_before (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  return attr_value_or_default (poppler_structure_element, Attribute::SpaceBefore)->getNum ();
}

/**
 * poppler_structure_element_get_space_after:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the amount of empty space after the block-level structure element.
 *
 * Return value: A positive value.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_space_after (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  return attr_value_or_default (poppler_structure_element, Attribute::SpaceAfter)->getNum ();
}

/**
 * poppler_structure_element_get_start_indent:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the amount of indentation at the beginning of the block-level structure element.
 *
 * Return value: A numeric value.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_start_indent (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  return attr_value_or_default (poppler_structure_element, Attribute::StartIndent)->getNum ();
}

/**
 * poppler_structure_element_get_end_indent:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the amount of indentation at the end of the block-level structure element.
 *
 * Return value: A numeric value.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_end_indent (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  return attr_value_or_default (poppler_structure_element, Attribute::EndIndent)->getNum ();
}

/**
 * poppler_structure_element_get_text_indent:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the amount of indentation of the text contained in the block-level structure element.
 *
 * Return value: A numeric value.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_text_indent (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  return attr_value_or_default (poppler_structure_element, Attribute::TextIndent)->getNum ();
}

/**
 * poppler_structure_element_get_text_align:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the text alignment mode of the text contained into a
 * block-level structure element.
 *
 * Return value: A #PopplerStructureTextAlign value.
 *
 * Since: 0.26
 */
PopplerStructureTextAlign
poppler_structure_element_get_text_align (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element),
                        EnumNameValue<PopplerStructureTextAlign>::values[0].value);
  return attr_to_enum<PopplerStructureTextAlign> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_bounding_box:
 * @poppler_structure_element: A #PopplerStructureElement
 * @bounding_box: (out): A #PopplerRectangle.
 *
 * Obtains the size of the bounding box of a block-level structure element.
 *
 * Return value: %TRUE if a bounding box is defined for the element,
 *    %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_get_bounding_box (PopplerStructureElement *poppler_structure_element,
                                            PopplerRectangle        *bounding_box)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), FALSE);
  g_return_val_if_fail (bounding_box != NULL, FALSE);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::BBox);
  if (value == NULL)
    return FALSE;

  gdouble dimensions[4];
  convert_double_or_4_doubles (value, dimensions);

  bounding_box->x1 = dimensions[0];
  bounding_box->y1 = dimensions[1];
  bounding_box->x2 = dimensions[2];
  bounding_box->y2 = dimensions[3];

  return TRUE;
}

/**
 * poppler_structure_element_get_width:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the width of the block-level structure element. Note that for elements which do
 * not specify a width, it has to be calculated, and in this case -1 is returned.
 *
 * Return value: A positive value if a width is defined, or -1
 *    if the width is to be calculated automatically.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_width (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Width);
  return value->isName ("Auto") ? -1.0 : value->getNum ();
}

/**
 * poppler_structure_element_get_height:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the height of the block-level structure element. Note that for elements which do
 * not specify a height, it has to be calculated, and in this case -1 is returned.
 *
 * Return value: A positive value if a width is defined, or -1
 *    if the height is to be calculated automatically.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_height (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element), NAN);
  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Height);
  return value->isName ("Auto") ? -1.0 : value->getNum ();
}

/**
 * poppler_structure_element_get_block_align:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the block-alignment mode of the block-level structure element.
 *
 * Return value: A #PopplerStructureBlockAlign value.
 *
 * Since: 0.26
 */
PopplerStructureBlockAlign
poppler_structure_element_get_block_align (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element),
                        EnumNameValue<PopplerStructureBlockAlign>::values[0].value);
  return attr_to_enum<PopplerStructureBlockAlign> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_inline_align:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the inline-alignment mode of the block-level structure element.
 *
 * Return value: A #PopplerStructureInlineAlign value.
 *
 * Since: 0.26
 */
PopplerStructureInlineAlign
poppler_structure_element_get_inline_align (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_block (poppler_structure_element),
                        EnumNameValue<PopplerStructureInlineAlign>::values[0].value);
  return attr_to_enum<PopplerStructureInlineAlign> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_table_border_style:
 * @poppler_structure_element: A #PopplerStructureElement
 * @border_styles: (out) (array fixed-size=4) (element-type PopplerStructureBorderStyle):
 *    An array of four #PopplerStructureBorderStyle elements.
 *
 * Obtains the table cell border style of a block-level structure element. The result values
 * are in before-after-start-end ordering. For example, using Western
 * left-to-right writing, that is top-bottom-left-right.
 *
 * Since: 0.26
 */
void
poppler_structure_element_get_table_border_style (PopplerStructureElement     *poppler_structure_element,
                                                  PopplerStructureBorderStyle *border_styles)
{
  g_return_if_fail (poppler_structure_element_is_block (poppler_structure_element));
  g_return_if_fail (border_styles != NULL);

  convert_border_style (attr_value_or_default (poppler_structure_element,
                                               Attribute::TBorderStyle),
                        border_styles);
}

/**
 * poppler_structure_element_get_table_padding:
 * @poppler_structure_element: A #PopplerStructureElement
 * @paddings: (out) (array fixed-size=4) (element-type gdouble):
 *    Padding for the four sides of the element.
 *
 * Obtains the padding between the table cell’s content rectangle and the
 * surrounding border of a block-level structure element. The result
 * values are in before-after-start-end ordering (for the typical
 * Western left-to-right writing, that is top-bottom-left-right).
 *
 * Since: 0.26
 */
void
poppler_structure_element_get_table_padding (PopplerStructureElement *poppler_structure_element,
                                             gdouble                 *paddings)
{
  g_return_if_fail (poppler_structure_element_is_block (poppler_structure_element));
  g_return_if_fail (paddings != NULL);

  convert_double_or_4_doubles (attr_value_or_default (poppler_structure_element,
                                                      Attribute::TPadding),
                               paddings);
}

/* Layout Attributes for inline-level structure elements */

/**
 * poppler_structure_element_get_baseline_shift:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains how much the text contained in the inline-level structure element should be shifted,
 * measuring from the baseline of the glyphs.
 *
 * Return value: A numeric value.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_baseline_shift (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element), NAN);
  return attr_value_or_default (poppler_structure_element, Attribute::BaselineShift)->getNum ();
}

/**
 * poppler_structure_element_get_line_height:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the line height for the text contained in the inline-level structure element.
 * Note that for elements which do not specify a line height, it has to be calculated,
 * and in this case -1 is returned.
 *
 * Return value: A positive value if a line height is defined, or -1
 *    if the height is to be calculated automatically.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_line_height (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element), NAN);
  Object *value = attr_value_or_default (poppler_structure_element, Attribute::LineHeight);
  return (value->isName ("Normal") || value->isName ("Auto")) ? -1.0 : value->getNum ();
}

/**
 * poppler_structure_element_get_text_decoration_color:
 * @poppler_structure_element: A #PopplerStructureElement
 * @color: (out): A #PopplerColor.
 *
 * Obtains the color of the text decoration for the text contained
 * in the inline-level structure element.
 * If this attribute is not specified, the color for this element shall be the current fill
 * color in effect at the start of its associated content.
 *
 * Return value: %TRUE if a color is defined for the element,
 *    %FALSE otherwise.
 *
 * Since: 0.26
 */
gboolean
poppler_structure_element_get_text_decoration_color (PopplerStructureElement *poppler_structure_element,
                                                     PopplerColor            *color)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element), FALSE);
  g_return_val_if_fail (color != NULL, FALSE);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::TextDecorationColor);
  if (value == NULL)
    return FALSE;

  convert_color (value, color);
  return FALSE;
}

/**
 * poppler_structure_element_get_text_decoration_thickness:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the thickness of the text decoration for the text contained
 * in the inline-level structure element.
 * If this attribute is not specified, it shall be derived from the current
 * stroke thickness in effect at the start of the element’s associated content.
 *
 * Return value: Thickness of the text decoration, or %NaN if not defined.
 *
 * Since: 0.26
 */
gdouble
poppler_structure_element_get_text_decoration_thickness (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element), NAN);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::TextDecorationThickness);
  return (value == NULL) ? NAN : value->getNum ();
}

/**
 * poppler_structure_element_get_text_decoration_type:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the text decoration type of the text contained in the
 * inline-level structure element.
 *
 * Return value: A #PopplerStructureTextDecoration value.
 *
 * Since: 0.26
 */
PopplerStructureTextDecoration
poppler_structure_element_get_text_decoration_type (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element),
                        EnumNameValue<PopplerStructureTextDecoration>::values[0].value);
  return attr_to_enum<PopplerStructureTextDecoration> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_ruby_align:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the alignment for the ruby text contained in a
 * inline-level structure element.
 *
 * Return value: A #PopplerStructureRubyAlign value.
 *
 * Since: 0.26
 */
PopplerStructureRubyAlign
poppler_structure_element_get_ruby_align (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element),
                        EnumNameValue<PopplerStructureRubyAlign>::values[0].value);
  return attr_to_enum<PopplerStructureRubyAlign> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_ruby_position:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the position for the ruby text contained in a
 * inline-level structure element.
 *
 * Return value: A #PopplerStructureRubyPosition value.
 *
 * Since: 0.26
 */
PopplerStructureRubyPosition
poppler_structure_element_get_ruby_position (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element),
                        EnumNameValue<PopplerStructureRubyPosition>::values[0].value);
  return attr_to_enum<PopplerStructureRubyPosition> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_glyph_orientation:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the glyph orientation for the text contained in a
 * inline-level structure element.
 *
 * Return value: A #PopplerStructureGlyphOrientation value.
 *
 * Since: 0.26
 */
PopplerStructureGlyphOrientation
poppler_structure_element_get_glyph_orientation (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_inline (poppler_structure_element),
                        EnumNameValue<PopplerStructureGlyphOrientation>::values[0].value);
  return attr_to_enum<PopplerStructureGlyphOrientation> (poppler_structure_element);
}

/* Column Attributes */

/**
 * poppler_structure_element_get_column_count:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the number of columns used to lay out the content contained
 * in the grouping element.
 *
 * Return value: Number of columns.
 *
 * Since: 0.26
 */
guint
poppler_structure_element_get_column_count (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_is_grouping (poppler_structure_element), 0);
  return static_cast<guint> (attr_value_or_default (poppler_structure_element,
                                                    Attribute::ColumnCount)->getInt ());
}

/**
 * poppler_structure_element_get_column_gaps:
 * @poppler_structure_element: A #PopplerStructureElement
 * @n_values: (out): Size of the returned array.
 *
 * Obtains the size of the gaps in between adjacent columns. Returns an
 * array of elements: the first one is the size of the gap in between
 * columns 1 and 2, second is the size between columns 2 and 3, and so on.
 *
 * For elements which use a single column, %NULL is returned and %n_values
 * is set to zero.
 *
 * If the attribute is undefined, %NULL is returned and %n_values is set
 * to a non-zero value.
 *
 * The array with the results is allocated by the function. When it is
 * not needed anymore, be sure to call g_free() on it.
 *
 * Return value: (transfer full) (array length=n_values) (element-type gdouble):
 *    Array containing the values for the column gaps, or %NULL if the
 *    array is empty or the attribute is not defined.
 *
 * Since: 0.26
 */
gdouble *
poppler_structure_element_get_column_gaps (PopplerStructureElement *poppler_structure_element,
                                           guint                   *n_values)
{
  g_return_val_if_fail (poppler_structure_element_is_grouping (poppler_structure_element), NULL);
  g_return_val_if_fail (n_values != NULL, NULL);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::ColumnGap);
  if (value == NULL)
    {
      *n_values = static_cast<guint> (-1);
      return NULL;
    }

  gdouble *result = NULL;
  convert_doubles_array (value, &result, n_values);
  return result;
}

/**
 * poppler_structure_element_get_column_widths:
 * @poppler_structure_element: A #PopplerStructureElement
 * @n_values: (out): Size of the returned array.
 *
 * Obtains an array with the widths of the columns.
 *
 * The array with the results is allocated by the function. When it is
 * not needed anymore, be sure to call g_free() on it.
 *
 * Return value: (transfer full) (array length=n_values) (element-type gdouble):
 *    Array containing widths of the columns, or %NULL if the attribute
 *    is not defined.
 *
 * Since: 0.26
 */
gdouble *
poppler_structure_element_get_column_widths (PopplerStructureElement *poppler_structure_element,
                                             guint                   *n_values)
{
  g_return_val_if_fail (poppler_structure_element_is_grouping (poppler_structure_element), NULL);
  g_return_val_if_fail (n_values != NULL, NULL);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::ColumnWidths);
  if (value == NULL)
    return NULL;

  gdouble *result = NULL;
  convert_doubles_array (value, &result, n_values);
  return result;
}

/* List Attribute */

/**
 * poppler_structure_element_get_list_numbering:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the list numbering style for list items.
 *
 * Return value: A #PopplerStructureListNumbering value.
 *
 * Since: 0.26
 */
PopplerStructureListNumbering
poppler_structure_element_get_list_numbering (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_LIST_ITEM,
                        EnumNameValue<PopplerStructureListNumbering>::values[0].value);
  return attr_to_enum<PopplerStructureListNumbering> (poppler_structure_element);
}

/* PrintField Attributes */

/**
 * poppler_structure_element_get_form_role:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the role of a form structure element that is part of a form, or is
 * a form field. This hints how the control for the element is intended
 * to be rendered.
 *
 * Return value: A #PopplerStructureFormRole value.
 *
 * Since: 0.26
 */
PopplerStructureFormRole
poppler_structure_element_get_form_role (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_FORM,
                        EnumNameValue<PopplerStructureFormRole>::values[0].value);

  /*
   * The Role attribute can actually be undefined.
   */
  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Role);
  if (value == NULL)
    return POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED;

  return name_to_enum<PopplerStructureFormRole> (value);
}

/**
 * poppler_structure_element_get_form_state:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * For a structure element that is a form field, obtains in which state
 * the associated control is expected to be rendered.
 *
 * Return value: A #PopplerStructureFormState value.
 *
 * Since: 0.26
 */
PopplerStructureFormState
poppler_structure_element_get_form_state (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_FORM,
                        EnumNameValue<PopplerStructureFormState>::values[0].value);
  return attr_to_enum<PopplerStructureFormState> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_form_description:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the textual description of the form element. Note that the
 * description is for informative purposes, and it is not intended
 * to be rendered. For example, assistive technologies may use the
 * description field to provide an alternate way of presenting an
 * element to the user.
 *
 * The returned string is allocated by the function. When it is
 * not needed anymore, be sure to call g_free() on it.
 *
 * Return value: (transfer full): A string, or %NULL if the attribute
 *    is not defined.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_form_description (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_FORM, NULL);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Desc);
  if (value == NULL)
    return NULL;
  if (value->isString ())
    return _poppler_goo_string_to_utf8 (value->getString ());
  if (value->isName ())
    return g_strdup (value->getName ());

  g_assert_not_reached ();
  return NULL;
}

/* Table Attributes */

/**
 * poppler_structure_element_get_table_row_span:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the number of rows the table element spans to.
 *
 * Return value: A positive, non-zero value.
 *
 * Since: 0.26
 */
guint
poppler_structure_element_get_table_row_span (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_TABLE, 0);
  return static_cast<guint> (attr_value_or_default (poppler_structure_element,
                                                    Attribute::RowSpan)->getInt ());
}

/**
 * poppler_structure_element_get_table_column_span:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the number of columns the table element spans to.
 *
 * Return value: A positive, non-zero value.
 *
 * Since: 0.26
 */
guint
poppler_structure_element_get_table_column_span (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_TABLE, 0);
  return static_cast<guint> (attr_value_or_default (poppler_structure_element,
                                                    Attribute::ColSpan)->getInt ());
}

/**
 * poppler_structure_element_get_table_headers:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains an array with the names of the table column headers. This is only
 * useful for table header row elements.
 *
 * The array with the results is allocated by the function. The number
 * of items in the returned array can be obtained with g_strv_length().
 * The returned value must be freed using g_strfreev().
 *
 * Return value: (transfer full) (array zero-terminated=1) (element-type gchar*):
 *    Zero-terminated array of strings with the table header names,
 *    or %NULL if the attribute is not defined.
 *
 * Since: 0.26
 */
gchar **
poppler_structure_element_get_table_headers (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_TABLE, NULL);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Headers);
  if (value == NULL)
    return NULL;

  g_assert (value->isArray ());

  const guint n_values = value->arrayGetLength ();
  gchar **result = g_new0 (gchar*, n_values + 1);

  for (guint i = 0; i < n_values; i++)
    {
      Object item;

      if (value->arrayGet (i, &item)->isString ())
        result[i] = _poppler_goo_string_to_utf8 (item.getString ());
      else if (item.isName ())
        result[i] = g_strdup (item.getName ());
      else
        g_assert_not_reached ();

      item.free ();
    }

  return result;
}

/**
 * poppler_structure_element_get_table_scope:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the scope of a table structure element.
 *
 * Return value: A #PopplerStructureScope value.
 *
 * Since: 0.26
 */
PopplerStructureTableScope
poppler_structure_element_get_table_scope (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (poppler_structure_element_get_kind (poppler_structure_element) == POPPLER_STRUCTURE_ELEMENT_TABLE,
                        EnumNameValue<PopplerStructureTableScope>::values[0].value);
  return attr_to_enum<PopplerStructureTableScope> (poppler_structure_element);
}

/**
 * poppler_structure_element_get_table_summary:
 * @poppler_structure_element: A #PopplerStructureElement
 *
 * Obtains the textual summary of the contents of the table element. Note that
 * the summary is meant for informative purposes, and it is not intended
 * to be rendered. For example, assistive technologies may use the
 * description field to provide an alternate way of presenting an element
 * to the user, or a document indexer may want to scan it for additional
 * keywords.
 *
 * The returned string is allocated by the function. When it is
 * not needed anymore, be sure to call g_free() on it.
 *
 * Return value: (transfer full): A string, or %NULL if the attribute
 *    is not defined.
 *
 * Since: 0.26
 */
gchar *
poppler_structure_element_get_table_summary (PopplerStructureElement *poppler_structure_element)
{
  g_return_val_if_fail (POPPLER_IS_STRUCTURE_ELEMENT (poppler_structure_element), NULL);

  Object *value = attr_value_or_default (poppler_structure_element, Attribute::Summary);
  if (value == NULL)
    return NULL;
  if (value->isString ())
    return _poppler_goo_string_to_utf8 (value->getString ());
  if (value->isName ())
    return g_strdup (value->getName ());

  g_assert_not_reached ();
  return NULL;
}
