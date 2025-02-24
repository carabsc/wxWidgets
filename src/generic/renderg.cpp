///////////////////////////////////////////////////////////////////////////////
// Name:        src/generic/renderg.cpp
// Purpose:     generic implementation of wxRendererNative (for any platform)
// Author:      Vadim Zeitlin
// Modified by:
// Created:     20.07.2003
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"


#include "wx/renderer.h"

#ifndef WX_PRECOMP
    #include "wx/string.h"
    #include "wx/dc.h"
    #include "wx/settings.h"
    #include "wx/gdicmn.h"
    #include "wx/module.h"
    #include "wx/control.h"
#endif //WX_PRECOMP

#include "wx/dcmirror.h"
#include "wx/math.h"
#include "wx/splitter.h"

#ifdef __WXMAC__
    #include "wx/osx/private.h"
#endif

#ifdef __WINDOWS__
    // We only need it to get ::MulDiv() declaration, used by wxMulDivInt32().
    #include "wx/msw/wrapwin.h"
#endif

// ----------------------------------------------------------------------------
// wxRendererGeneric: our wxRendererNative implementation
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxRendererGeneric : public wxRendererNative
{
public:
    wxRendererGeneric();

    virtual int  DrawHeaderButton(wxWindow *win,
                                  wxDC& dc,
                                  const wxRect& rect,
                                  int flags = 0,
                                  wxHeaderSortIconType sortArrow = wxHDR_SORT_ICON_NONE,
                                  wxHeaderButtonParams* params = NULL) wxOVERRIDE;

    virtual int  DrawHeaderButtonContents(wxWindow *win,
                                          wxDC& dc,
                                          const wxRect& rect,
                                          int flags = 0,
                                          wxHeaderSortIconType sortArrow = wxHDR_SORT_ICON_NONE,
                                          wxHeaderButtonParams* params = NULL) wxOVERRIDE;

    virtual int GetHeaderButtonHeight(wxWindow *win) wxOVERRIDE;

    virtual int GetHeaderButtonMargin(wxWindow *win) wxOVERRIDE;

    virtual void DrawTreeItemButton(wxWindow *win,
                                    wxDC& dc,
                                    const wxRect& rect,
                                    int flags = 0) wxOVERRIDE;

    virtual void DrawTreeItemBackground(wxWindow *win,
                                        wxDC& dc,
                                        const wxRect& rect,
                                        int flags = 0) wxOVERRIDE;

    virtual void DrawSplitterBorder(wxWindow *win,
                                    wxDC& dc,
                                    const wxRect& rect,
                                    int flags = 0) wxOVERRIDE;

    virtual void DrawSplitterSash(wxWindow *win,
                                  wxDC& dc,
                                  const wxSize& size,
                                  wxCoord position,
                                  wxOrientation orient,
                                  int flags = 0) wxOVERRIDE;

    virtual void DrawComboBoxDropButton(wxWindow *win,
                                        wxDC& dc,
                                        const wxRect& rect,
                                        int flags = 0) wxOVERRIDE;

    virtual void DrawDropArrow(wxWindow *win,
                               wxDC& dc,
                               const wxRect& rect,
                               int flags = 0) wxOVERRIDE;

    virtual void DrawCheckBox(wxWindow *win,
                              wxDC& dc,
                              const wxRect& rect,
                              int flags = 0) wxOVERRIDE;

    virtual void DrawCheckMark(wxWindow *win,
                               wxDC& dc,
                               const wxRect& rect,
                               int flags = 0) wxOVERRIDE;

    virtual wxSize GetCheckBoxSize(wxWindow *win, int flags = 0) wxOVERRIDE;

    virtual wxSize GetCheckMarkSize(wxWindow *win) wxOVERRIDE;

    virtual wxSize GetExpanderSize(wxWindow *win) wxOVERRIDE;

    virtual wxSize GetButtonPaddingSize(wxWindow *win, wxDC& dc) wxOVERRIDE;

    virtual void DrawPushButton(wxWindow *win,
                                wxDC& dc,
                                const wxRect& rect,
                                int flags = 0) wxOVERRIDE;

    virtual void DrawCollapseButton(wxWindow *win,
        wxDC& dc,
        const wxRect& rect,
        int flags = 0) wxOVERRIDE;

    virtual wxSize GetCollapseButtonSize(wxWindow *win, wxDC& dc) wxOVERRIDE;

    virtual void DrawItemSelectionRect(wxWindow *win,
                                       wxDC& dc,
                                       const wxRect& rect,
                                       int flags = 0) wxOVERRIDE;

    virtual void DrawFocusRect(wxWindow* win, wxDC& dc, const wxRect& rect, int flags = 0) wxOVERRIDE;

    virtual void DrawChoice(wxWindow* win, wxDC& dc, const wxRect& rect, int flags=0) wxOVERRIDE;

    virtual void DrawComboBox(wxWindow* win, wxDC& dc, const wxRect& rect, int flags=0) wxOVERRIDE;

    virtual void DrawTextCtrl(wxWindow* win, wxDC& dc, const wxRect& rect, int flags=0) wxOVERRIDE;

    virtual void DrawRadioBitmap(wxWindow* win, wxDC& dc, const wxRect& rect, int flags=0) wxOVERRIDE;

#ifdef wxHAS_DRAW_TITLE_BAR_BITMAP
    virtual void DrawTitleBarBitmap(wxWindow *win,
                                    wxDC& dc,
                                    const wxRect& rect,
                                    wxTitleBarButton button,
                                    int flags = 0) wxOVERRIDE;
#endif // wxHAS_DRAW_TITLE_BAR_BITMAP

    virtual void DrawGauge(wxWindow* win, wxDC& dc, const wxRect& rect, int value, int max, int flags = 0) wxOVERRIDE;

    virtual void DrawItemText(wxWindow* win,
                              wxDC& dc,
                              const wxString& text,
                              const wxRect& rect,
                              int align = wxALIGN_LEFT | wxALIGN_TOP,
                              int flags = 0,
                              wxEllipsizeMode ellipsizeMode = wxELLIPSIZE_END) wxOVERRIDE;

    virtual void DrawToolbarButton(wxWindow* win,
                                   wxDC& dc,
                                   const wxRect& rect,
                                   int flags = 0) wxOVERRIDE;

    virtual void DrawTabControlBackground(wxWindow* win,
                                          wxDC& dc,
                                          const wxRect& rect,
                                          int flags = 0) wxOVERRIDE;

    virtual void DrawTabControlTab(wxWindow* win,
                                   wxDC& dc,
                                   const wxRect& rect,
                                   int flags = 0) wxOVERRIDE;

    virtual wxSplitterRenderParams GetSplitterParams(const wxWindow *win) wxOVERRIDE;

    virtual wxRendererVersion GetVersion() const wxOVERRIDE
    {
        return wxRendererVersion(wxRendererVersion::Current_Version,
                                 wxRendererVersion::Current_Age);
    }


    // Cleanup by deleting standard renderer
    static void Cleanup();

    // Get the generic object
    static wxRendererGeneric* DoGetGeneric();

protected:
    // draw the rectangle using the first pen for the left and top sides and
    // the second one for the bottom and right ones
    void DrawShadedRect(wxDC& dc, wxRect *rect,
                        const wxPen& pen1, const wxPen& pen2);

    // the standard pens
    wxPen m_penBlack,
          m_penDarkGrey,
          m_penLightGrey,
          m_penHighlight;

    static wxRendererGeneric* sm_rendererGeneric;
};

// ----------------------------------------------------------------------------
// misc. drawing functions
// ----------------------------------------------------------------------------

// Draw focus rect for individual cell. Unlike native focus rect, we render
// this in foreground text color (typically white) to enhance contrast and
// make it visible.
static void DrawSelectedCellFocusRect(wxDC& dc, const wxRect& rect)
{
    // (This code is based on wxRendererGeneric::DrawFocusRect and modified.)

    // draw the pixels manually because the "dots" in wxPen with wxPENSTYLE_DOT style
    // may be short traits and not really dots
    //
    // note that to behave in the same manner as DrawRect(), we must exclude
    // the bottom and right borders from the rectangle
    wxCoord x1 = rect.GetLeft(),
        y1 = rect.GetTop(),
        x2 = rect.GetRight(),
        y2 = rect.GetBottom();

    wxDCPenChanger pen(dc, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

    wxCoord z;
    for (z = x1 + 1; z < x2; z += 2)
        dc.DrawPoint(z, rect.GetTop());

    wxCoord shift = z == x2 ? 0 : 1;
    for (z = y1 + shift; z < y2; z += 2)
        dc.DrawPoint(x2, z);

    shift = z == y2 ? 0 : 1;
    for (z = x2 - shift; z > x1; z -= 2)
        dc.DrawPoint(z, y2);

    shift = z == x1 ? 0 : 1;
    for (z = y2 - shift; z > y1; z -= 2)
        dc.DrawPoint(x1, z);
}

// ============================================================================
// wxRendererGeneric implementation
// ============================================================================

// Get the generic object
wxRendererGeneric* wxRendererGeneric::DoGetGeneric()
{
    if (!sm_rendererGeneric)
        sm_rendererGeneric = new wxRendererGeneric;
    return sm_rendererGeneric;
}

// ----------------------------------------------------------------------------
// wxRendererGeneric creation
// ----------------------------------------------------------------------------

/* static */
wxRendererNative& wxRendererNative::GetGeneric()
{
    return * wxRendererGeneric::DoGetGeneric();
}

void wxRendererGeneric::Cleanup()
{
    wxDELETE(sm_rendererGeneric);
}

wxRendererGeneric* wxRendererGeneric::sm_rendererGeneric = NULL;

wxRendererGeneric::wxRendererGeneric()
    : m_penBlack(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW)),
      m_penDarkGrey(wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW)),
      m_penLightGrey(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)),
      m_penHighlight(wxSystemSettings::GetColour(wxSYS_COLOUR_3DHIGHLIGHT))
{
}

// ----------------------------------------------------------------------------
// wxRendererGeneric helpers
// ----------------------------------------------------------------------------

void
wxRendererGeneric::DrawShadedRect(wxDC& dc,
                                  wxRect *rect,
                                  const wxPen& pen1,
                                  const wxPen& pen2)
{
    // draw the rectangle
    wxDCPenChanger setPen(dc, pen1);
    dc.DrawLine(rect->GetLeft(), rect->GetTop(),
                rect->GetLeft(), rect->GetBottom());
    dc.DrawLine(rect->GetLeft() + 1, rect->GetTop(),
                rect->GetRight(), rect->GetTop());
    dc.SetPen(pen2);
    dc.DrawLine(rect->GetRight(), rect->GetTop(),
                rect->GetRight(), rect->GetBottom());
    dc.DrawLine(rect->GetLeft(), rect->GetBottom(),
                rect->GetRight() + 1, rect->GetBottom());

    // adjust the rect
    rect->Inflate(-1);
}

// ----------------------------------------------------------------------------
// tree/list ctrl drawing
// ----------------------------------------------------------------------------

int
wxRendererGeneric::DrawHeaderButton(wxWindow* win,
                                    wxDC& dc,
                                    const wxRect& rect,
                                    int flags,
                                    wxHeaderSortIconType sortArrow,
                                    wxHeaderButtonParams* params)
{
    const wxCoord x = rect.x,
                  y = rect.y,
                  w = rect.width,
                  h = rect.height;

    wxDCBrushChanger setBrush(dc, wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)));
    wxDCPenChanger setPen(dc, *wxTRANSPARENT_PEN);
    dc.DrawRectangle(rect);

    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    dc.SetPen(m_penBlack);
    dc.DrawLine( x+w-1, y, x+w-1, y+h );  // right (outer)
    dc.DrawLine( x, y+h-1, x+w, y+h-1 );  // bottom (outer)

    dc.SetPen(m_penDarkGrey);
    dc.DrawLine( x+w-2, y+1, x+w-2, y+h-1 );  // right (inner)
    dc.DrawLine( x+1, y+h-2, x+w-1, y+h-2 );  // bottom (inner)

    dc.SetPen(m_penHighlight);
    dc.DrawLine( x, y, x, y+h-1 ); // left (outer)
    dc.DrawLine( x, y, x+w-1, y ); // top (outer)

    return DrawHeaderButtonContents(win, dc, rect, flags, sortArrow, params);
}


int
wxRendererGeneric::DrawHeaderButtonContents(wxWindow *win,
                                            wxDC& dc,
                                            const wxRect& rect,
                                            int flags,
                                            wxHeaderSortIconType sortArrow,
                                            wxHeaderButtonParams* params)
{
    int labelWidth = 0;

    // Mark this item as selected.  For the generic version we'll just draw an
    // underline
    if ( flags & wxCONTROL_SELECTED )
    {
        // draw a line at the bottom of the header button, overlaying the
        // native hot-tracking line (on XP)
        const int penwidth = 3;
        int y = rect.y + rect.height + 1 - penwidth;
        wxColour c = (params && params->m_selectionColour.IsOk()) ?
            params->m_selectionColour : wxColour(0x66, 0x66, 0x66);
        wxPen pen(c, penwidth);
        pen.SetCap(wxCAP_BUTT);
        wxDCPenChanger setPen(dc, pen);
        dc.DrawLine(rect.x, y, rect.x + rect.width, y);
    }

    // Draw an up or down arrow
    int arrowSpace = 0;
    if (sortArrow != wxHDR_SORT_ICON_NONE )
    {
        wxRect ar = rect;

        // make a rect for the arrow
        ar.SetSize(wxWindow::FromDIP(wxSize(8, 4), win));
        ar.y += (rect.height - ar.height)/2;
        ar.x = ar.x + rect.width - 3*ar.width/2;
        arrowSpace = 3*ar.width/2; // space to preserve when drawing the label

        wxPoint triPt[3];
        if ( sortArrow & wxHDR_SORT_ICON_UP )
        {
            triPt[0].x = ar.width / 2;
            triPt[0].y = 0;
            triPt[1].x = ar.width;
            triPt[1].y = ar.height;
            triPt[2].x = 0;
            triPt[2].y = ar.height;
        }
        else
        {
            triPt[0].x = 0;
            triPt[0].y = 0;
            triPt[1].x = ar.width;
            triPt[1].y = 0;
            triPt[2].x = ar.width / 2;
            triPt[2].y = ar.height;
        }

        wxColour c = (params && params->m_arrowColour.IsOk()) ?
            params->m_arrowColour : wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW);

        wxDCPenChanger setPen(dc, c);
        wxDCBrushChanger setBrush(dc, c);

        wxDCClipper clip(dc, rect);
        dc.DrawPolygon( 3, triPt, ar.x, ar.y);
    }
    labelWidth += arrowSpace;

    // short-circuit if no params exist
    if ( !params ) return labelWidth;

    const int bmp_margin = 1; // an extra pixel on either side of the bitmap
    const int txt_margin = 5; // number of pixels to reserve on either side of the label

    // get the dimensions of the bitmap, if any, and of the label text
    int w = -1;
    int h = -1;
    int availWidth = rect.width;
    if ( params->m_labelBitmap.IsOk() )
    {
        w = params->m_labelBitmap.GetLogicalWidth();
        h = params->m_labelBitmap.GetLogicalHeight();
        labelWidth = 2*bmp_margin + w;
        availWidth -= labelWidth;
    }
    wxString label( params->m_labelText );
    int tw, th, td;
    wxFont font = params->m_labelFont.IsOk() ? params->m_labelFont : win->GetFont();
    wxDCFontChanger setFont(dc, font);
    if ( !label.empty() )
    {
        dc.GetTextExtent( label, &tw, &th, &td );
        labelWidth += 2*txt_margin;
        availWidth -= 2*txt_margin;
#if wxUSE_CONTROLS
        if ( tw > availWidth )
        {
            label = wxControl::Ellipsize(label,
                                         dc,
                                         wxELLIPSIZE_END,
                                         availWidth,
                                         wxELLIPSIZE_FLAGS_NONE);
            tw = dc.GetTextExtent(label).x;
        }
#endif // wxUSE_CONTROLS
        labelWidth += tw;
        availWidth -= tw;
    }

    // calculate position of left edge of label text
    int label_x = rect.x;
    switch (params->m_labelAlignment)
    {
        default:
        case wxALIGN_LEFT:
            break;

        case wxALIGN_CENTER:
            label_x += availWidth / 2;
            break;

        case wxALIGN_RIGHT:
            label_x += availWidth;
            break;
    }
    // calculate the position of the bitmap
    int bmp_x = label_x;
    if ((w != -1) && (!label.empty()))
    {
        switch (params->m_bitmapAlignment)
        {
            default:
            case wxALIGN_LEFT:
                // shift the label right to open space for the bitmap
                label_x += w + 2*bmp_margin;
                break;

            case wxALIGN_RIGHT:
                bmp_x += tw + 2*txt_margin;
                break;
        }
    }

    // draw the bitmap if there is one
    if ( params->m_labelBitmap.IsOk() )
    {
        const int y = rect.y + wxMax(1, (rect.height - h) / 2);
        wxDCClipper clip(dc, rect);
        dc.DrawBitmap(params->m_labelBitmap, bmp_x + bmp_margin, y, true);
    }

    // draw a label if one is given
    if ( !params->m_labelText.empty() )
    {
        wxColour clr = params->m_labelColour.IsOk() ?
            params->m_labelColour : win->GetForegroundColour();
        wxDCTextColourChanger setTextFg(dc, clr);
        wxDCTextBgModeChanger setBgMode(dc, wxBRUSHSTYLE_TRANSPARENT);
        const int y = rect.y + wxMax(0, (rect.height - (th+td)) / 2);
        dc.DrawText(label, label_x + txt_margin, y);
    }

    return labelWidth;
}


int wxRendererGeneric::GetHeaderButtonHeight(wxWindow *win)
{
    // Copied and adapted from src/generic/listctrl.cpp
    const int HEADER_OFFSET_Y = 1;
    const int EXTRA_HEIGHT = 4;

    int w=0, h=14, d=0;
    if (win)
        win->GetTextExtent(wxT("Hg"), &w, &h, &d);

    return h + d + 2 * HEADER_OFFSET_Y + EXTRA_HEIGHT;
}

int wxRendererGeneric::GetHeaderButtonMargin(wxWindow *WXUNUSED(win))
{
    return 5;
}


// draw the plus or minus sign
void
wxRendererGeneric::DrawTreeItemButton(wxWindow * WXUNUSED(win),
                                      wxDC& dc,
                                      const wxRect& rect,
                                      int flags)
{
    // store settings
    wxDCPenChanger penChanger(dc, *wxGREY_PEN);
    wxDCBrushChanger brushChanger(dc, *wxWHITE_BRUSH);

    dc.DrawRectangle(rect);

    // black lines
    const wxCoord xMiddle = rect.x + rect.width/2;
    const wxCoord yMiddle = rect.y + rect.height/2;

    // half of the length of the horz lines in "-" and "+"
    const wxCoord halfWidth = rect.width/2 - 2;
    wxDCPenChanger setPen(dc, *wxBLACK_PEN);
    dc.DrawLine(xMiddle - halfWidth, yMiddle,
                xMiddle + halfWidth + 1, yMiddle);

    if ( !(flags & wxCONTROL_EXPANDED) )
    {
        // turn "-" into "+"
        const wxCoord halfHeight = rect.height/2 - 2;
        dc.DrawLine(xMiddle, yMiddle - halfHeight,
                    xMiddle, yMiddle + halfHeight + 1);
    }
}

// draw the background
void
wxRendererGeneric::DrawTreeItemBackground(wxWindow * WXUNUSED(win),
                                          wxDC& dc,
                                          const wxRect& rect,
                                          int flags)
{
    if (flags & wxCONTROL_CURRENT)
    {
        wxColour highclr = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
        wxDCPenChanger penChanger(dc, wxPen(highclr));
        wxDCBrushChanger brushChanger(dc, wxBrush(highclr.ChangeLightness(wxSystemSettings::GetAppearance().IsDark() ? 40 : 170)));
        dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
        return;
    }
    dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
}

// ----------------------------------------------------------------------------
// sash drawing
// ----------------------------------------------------------------------------

wxSplitterRenderParams
wxRendererGeneric::GetSplitterParams(const wxWindow *win)
{
    // see below
    wxCoord sashWidth,
            border;

    if ( win->HasFlag(wxSP_3DSASH) )
        sashWidth = 7;
    else if ( win->HasFlag(wxSP_NOSASH) )
        sashWidth = 0;
    else // no 3D effect
        sashWidth = 3;

    if ( win->HasFlag(wxSP_3DBORDER) )
        border = 2;
    else // no 3D effect
        border = 0;

    return wxSplitterRenderParams(sashWidth, border, false);
}

void
wxRendererGeneric::DrawSplitterBorder(wxWindow *win,
                                      wxDC& dc,
                                      const wxRect& rectOrig,
                                      int WXUNUSED(falgs))
{
    if ( win->HasFlag(wxSP_3DBORDER) )
    {
        wxRect rect = rectOrig;
        DrawShadedRect(dc, &rect, m_penDarkGrey, m_penHighlight);
        DrawShadedRect(dc, &rect, m_penBlack, m_penLightGrey);
    }
}

void
wxRendererGeneric::DrawSplitterSash(wxWindow *win,
                                    wxDC& dcReal,
                                    const wxSize& sizeReal,
                                    wxCoord position,
                                    wxOrientation orient,
                                    int WXUNUSED(flags))
{
    // to avoid duplicating the same code for horizontal and vertical sashes,
    // simply mirror the DC instead if needed (i.e. if horz splitter)
    wxMirrorDC dc(dcReal, orient != wxVERTICAL);
    wxSize size = dc.Reflect(sizeReal);


    // we draw a Win32-like grey sash with possible 3D border here:
    //
    //   ---- this is position
    //  /
    // v
    // dWGGGDd
    // GWGGGDB
    // GWGGGDB  where G is light grey (face)
    // GWGGGDB        W    white      (light)
    // GWGGGDB        D    dark grey  (shadow)
    // GWGGGDB        B    black      (dark shadow)
    // GWGGGDB
    // GWGGGDB  and lower letters are our border (already drawn)
    // GWGGGDB
    // wWGGGDd
    //
    // only the middle 3 columns are drawn unless wxSP_3D is specified

    const wxCoord h = size.y;
    wxCoord offset = 0;

    // If we're drawing the border, draw the sash 3d lines shorter
    if ( win->HasFlag(wxSP_3DBORDER) )
    {
        offset = 1;
    }

    wxDCPenChanger setPen(dc, *wxTRANSPARENT_PEN);

    if ( win->HasFlag(wxSP_3DSASH) )
    {
        // Draw the 3D sash
        wxDCBrushChanger setBrush(dc, wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)));
        dc.DrawRectangle(position + 2, 0, 3, h);

        dc.SetPen(m_penLightGrey);
        dc.DrawLine(position, offset, position, h - offset);

        dc.SetPen(m_penHighlight);
        dc.DrawLine(position + 1, 0, position + 1, h);

        dc.SetPen(m_penDarkGrey);
        dc.DrawLine(position + 5, 0, position + 5, h);

        dc.SetPen(m_penBlack);
        dc.DrawLine(position + 6, offset, position + 6, h - offset);
    }
    else
    {
        // Draw a flat sash
        wxDCBrushChanger setBrush(dc, wxBrush(win->GetBackgroundColour()));
        dc.DrawRectangle(position, 0, 3, h);
    }
}

// ----------------------------------------------------------------------------
// button drawing
// ----------------------------------------------------------------------------

void
wxRendererGeneric::DrawComboBoxDropButton(wxWindow *win,
                                          wxDC& dc,
                                          const wxRect& rect,
                                          int flags)
{
    DrawPushButton(win,dc,rect,flags);
    DrawDropArrow(win,dc,rect,flags);
}

void
wxRendererGeneric::DrawDropArrow(wxWindow *win,
                                 wxDC& dc,
                                 const wxRect& rect,
                                 int WXUNUSED(flags))
{
    // This generic implementation should be good
    // enough for Windows platforms (including XP).

    int arrowHalf = rect.width/5;
    int rectMid = rect.width / 2;
    int arrowTopY = (rect.height/2) - (arrowHalf/2);

    // This should always result in arrow with odd width.
    wxPoint pt[] =
    {
        wxPoint(rectMid - arrowHalf, arrowTopY),
        wxPoint(rectMid + arrowHalf, arrowTopY),
        wxPoint(rectMid, arrowTopY + arrowHalf)
    };
    wxDCBrushChanger setBrush(dc, wxBrush(win->GetForegroundColour()));
    wxDCPenChanger setPen(dc, wxPen(win->GetForegroundColour()));
    dc.DrawPolygon(WXSIZEOF(pt), pt, rect.x, rect.y);
}

void
wxRendererGeneric::DrawCheckBox(wxWindow *WXUNUSED(win),
                                wxDC& dc,
                                const wxRect& rect,
                                int flags)
{
    wxDCPenChanger setPen(dc, *(flags & wxCONTROL_DISABLED ? wxGREY_PEN : wxBLACK_PEN));
    wxDCBrushChanger setBrush(dc, *wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(rect);

    if ( flags & wxCONTROL_CHECKED )
    {
        dc.DrawCheckMark(rect.Deflate(2, 2));
    }
}

void
wxRendererGeneric::DrawCheckMark(wxWindow *WXUNUSED(win),
                                 wxDC& dc,
                                 const wxRect& rect,
                                 int flags)
{
    wxDCPenChanger setPen(dc, *(flags & wxCONTROL_DISABLED ? wxGREY_PEN : wxBLACK_PEN));
    dc.DrawCheckMark(rect);
}

wxSize wxRendererGeneric::GetCheckBoxSize(wxWindow *win, int WXUNUSED(flags))
{
    wxCHECK_MSG( win, wxSize(0, 0), "Must have a valid window" );

    return win->FromDIP(wxSize(16, 16));
}

wxSize wxRendererGeneric::GetCheckMarkSize(wxWindow *win)
{
    return GetCheckBoxSize(win, wxCONTROL_CELL);
}

wxSize wxRendererGeneric::GetExpanderSize(wxWindow *win)
{
    wxCHECK_MSG( win, wxSize(0, 0), "Must have a valid window" );

    return win->FromDIP(wxSize(16, 16));
}

wxSize wxRendererGeneric::GetButtonPaddingSize(wxWindow *win, wxDC& WXUNUSED(dc))
{
    wxCHECK_MSG( win, wxSize(0, 0), "Must have a valid window" );

    return win->FromDIP(wxSize(3, 3));
}

void
wxRendererGeneric::DrawPushButton(wxWindow *win,
                                  wxDC& dc,
                                  const wxRect& rect,
                                  int flags)
{
    // Don't try anything too fancy. It'll just turn out looking
    // out-of-place on most platforms.
    wxColour bgCol = flags & wxCONTROL_DISABLED ?
                        wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE) :
                        win->GetBackgroundColour();
    wxDCBrushChanger setBrush(dc, wxBrush(bgCol));
    wxDCPenChanger setPen(dc, wxPen(bgCol));
    dc.DrawRectangle(rect);
}

void
wxRendererGeneric::DrawCollapseButton(wxWindow *win,
                                wxDC& dc,
                                const wxRect& rect,
                                int flags)
{
    int arrowHalf = rect.width / 5;
    int rectMid = rect.width / 2;
    int arrowTopY = (rect.height / 2) - (arrowHalf / 2);

    wxPoint pt[3];
    if (flags & wxCONTROL_EXPANDED)
    {
        // This should always result in arrow with odd width.
        pt[0] = wxPoint(rectMid - arrowHalf, arrowTopY);
        pt[1] = wxPoint(rectMid + arrowHalf, arrowTopY);
        pt[2] = wxPoint(rectMid, arrowTopY + arrowHalf);
    }
    else
    {
        // This should always result in arrow with odd height.
        pt[0] = wxPoint(arrowTopY, rectMid - arrowHalf);
        pt[1] = wxPoint(arrowTopY + arrowHalf, rectMid);
        pt[2] = wxPoint(arrowTopY, rectMid + arrowHalf);
    }

    wxDCBrushChanger setBrush(dc, wxBrush(win->GetForegroundColour()));
    wxDCPenChanger setPen(dc, wxPen(win->GetForegroundColour()));
    dc.DrawPolygon(WXSIZEOF(pt), pt, rect.x, rect.y);
}

wxSize wxRendererGeneric::GetCollapseButtonSize(wxWindow *WXUNUSED(win), wxDC& WXUNUSED(dc))
{
    return wxSize(18, 18);
}

void
wxRendererGeneric::DrawItemSelectionRect(wxWindow * WXUNUSED(win),
                                         wxDC& dc,
                                         const wxRect& rect,
                                         int flags)
{
    wxBrush brush;
    if ( flags & wxCONTROL_SELECTED )
    {
        if ( flags & wxCONTROL_FOCUSED )
        {
            brush = wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
        }
        else // !focused
        {
            brush = wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
        }
    }
    else // !selected
    {
        brush = *wxTRANSPARENT_BRUSH;
    }

    wxDCBrushChanger setBrush(dc, brush);
    bool drawFocusRect = (flags & wxCONTROL_CURRENT) && (flags & wxCONTROL_FOCUSED);

    bool blackPen = drawFocusRect && !(flags & wxCONTROL_CELL);
    wxDCPenChanger setPen(dc, *(blackPen ? wxBLACK_PEN : wxTRANSPARENT_PEN));

    dc.DrawRectangle( rect );

    if ( drawFocusRect && (flags & wxCONTROL_CELL) )
    {
        wxRect focusRect(rect);
        focusRect.Deflate(1);

        DrawSelectedCellFocusRect(dc, focusRect);
    }
}

void
wxRendererGeneric::DrawFocusRect(wxWindow* WXUNUSED(win), wxDC& dc, const wxRect& rect, int WXUNUSED(flags))
{
    // draw the pixels manually because the "dots" in wxPen with wxPENSTYLE_DOT style
    // may be short traits and not really dots
    //
    // note that to behave in the same manner as DrawRect(), we must exclude
    // the bottom and right borders from the rectangle
    wxCoord x1 = rect.GetLeft(),
            y1 = rect.GetTop(),
            x2 = rect.GetRight(),
            y2 = rect.GetBottom();

    wxDCPenChanger setPen(dc, m_penBlack);

#ifdef __WXMAC__
    dc.SetLogicalFunction(wxCOPY);
#else
    // this seems to be closer than what Windows does than wxINVERT although
    // I'm still not sure if it's correct
    dc.SetLogicalFunction(wxAND_REVERSE);
#endif

    wxCoord z;
    for ( z = x1 + 1; z < x2; z += 2 )
        dc.DrawPoint(z, rect.GetTop());

    wxCoord shift = z == x2 ? 0 : 1;
    for ( z = y1 + shift; z < y2; z += 2 )
        dc.DrawPoint(x2, z);

    shift = z == y2 ? 0 : 1;
    for ( z = x2 - shift; z > x1; z -= 2 )
        dc.DrawPoint(z, y2);

    shift = z == x1 ? 0 : 1;
    for ( z = y2 - shift; z > y1; z -= 2 )
        dc.DrawPoint(x1, z);

    dc.SetLogicalFunction(wxCOPY);
}

void wxRendererGeneric::DrawChoice(wxWindow* WXUNUSED(win), wxDC& WXUNUSED(dc),
                           const wxRect& WXUNUSED(rect), int WXUNUSED(flags))
{
    wxFAIL_MSG("UNIMPLEMENTED: wxRendererGeneric::DrawChoice");
}

void wxRendererGeneric::DrawComboBox(wxWindow* WXUNUSED(win), wxDC& WXUNUSED(dc),
                           const wxRect& WXUNUSED(rect), int WXUNUSED(flags))
{
    wxFAIL_MSG("UNIMPLEMENTED: wxRendererGeneric::DrawComboBox");
}

void wxRendererGeneric::DrawRadioBitmap(wxWindow* WXUNUSED(win), wxDC& WXUNUSED(dc),
                           const wxRect& WXUNUSED(rect), int WXUNUSED(flags))
{
    wxFAIL_MSG("UNIMPLEMENTED: wxRendererGeneric::DrawRadioBitmap");
}

void wxRendererGeneric::DrawTextCtrl(wxWindow* WXUNUSED(win),
                                     wxDC& dc,
                                     const wxRect& rect,
                                     int WXUNUSED(flags))
{
    wxColour fill;
    wxColour bdr;
    {
        fill = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
        bdr = *wxBLACK;
    }

    wxDCPenChanger setPen(dc, bdr);
    wxDCBrushChanger setBrush(dc, fill);
    dc.DrawRectangle(rect);
}

#ifdef wxHAS_DRAW_TITLE_BAR_BITMAP

void wxRendererGeneric::DrawTitleBarBitmap(wxWindow * WXUNUSED(win),
                                           wxDC& WXUNUSED(dc),
                                           const wxRect& WXUNUSED(rect),
                                           wxTitleBarButton WXUNUSED(button),
                                           int WXUNUSED(flags))
{
    // no need to fail here, if wxHAS_DRAW_TITLE_BAR_BITMAP is defined this
    // will be implemented in the native renderer and this version is never
    // going to be used -- but we still need to define it to allow
    // instantiation of this class (which would have been pure virtual
    // otherwise)
}

#endif // wxHAS_DRAW_TITLE_BAR_BITMAP

void wxRendererGeneric::DrawGauge(wxWindow* win,
                                  wxDC& dc,
                                  const wxRect& rect,
                                  int value,
                                  int max,
                                  int flags)
{
    // This is a hack, but we want to allow customizing the colour used for the
    // gauge body, as this is important for the generic wxDataViewCtrl
    // implementation which uses this method. So we assume that if the caller
    // had set up a brush using background colour different from the default,
    // it should be used. Otherwise we use the default one.
    const wxBrush& bg = dc.GetBackground();
    wxColour colBar;
    if ( bg.IsOk() && bg.GetColour() != win->GetBackgroundColour() )
        colBar = bg.GetColour();
    else
        colBar = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);

    // Use same background as text controls.
    DrawTextCtrl(win, dc, rect);

    // Calculate the progress bar size.
    wxRect progRect(rect);
    progRect.Deflate(2);
    if ( flags & wxCONTROL_SPECIAL )
    {
        const int h = wxMulDivInt32(progRect.height, value, max);
        progRect.y += progRect.height - h;
        progRect.height = h;
    }
    else // Horizontal.
    {
        progRect.width = wxMulDivInt32(progRect.width, value, max);
    }

    wxDCBrushChanger setBrush(dc, colBar);
    wxDCPenChanger setPen(dc, *wxTRANSPARENT_PEN);
    dc.DrawRectangle(progRect);
}

void
wxRendererGeneric::DrawItemText(wxWindow* WXUNUSED(win),
                                wxDC& dc,
                                const wxString& text,
                                const wxRect& rect,
                                int align,
                                int flags,
                                wxEllipsizeMode ellipsizeMode)
{
    // Determine text color
    wxColour textColour;
    if ( flags & wxCONTROL_SELECTED )
    {
        textColour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT);
    }
    else if ( flags & wxCONTROL_DISABLED )
    {
        textColour = wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT);
    }

    // Be careful to avoid using the default flags here as otherwise any
    // ampersands in the text would be consumed (and tabs expanded).
    const wxString paintText = wxControl::Ellipsize(text, dc,
                                                    ellipsizeMode,
                                                    rect.GetWidth(),
                                                    wxELLIPSIZE_FLAGS_NONE);

    // Draw text taking care not to change its colour if it had been set by the
    // caller for a normal item to allow having items in non-default colours.
    wxDCTextColourChanger setTextFg(dc);
    if ( textColour.IsOk() )
        setTextFg.Set(textColour);
    wxDCTextBgColourChanger setTextBg(dc, wxTransparentColour);
    dc.DrawLabel(paintText, rect, align);
}

// draw a skeleton toolbar button (just the background and the frame)
void wxRendererGeneric::DrawToolbarButton(wxWindow* WXUNUSED(win), wxDC& dc,
                                          const wxRect& rect, int flags)
{
    wxColour high = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT);
    bool dark = wxSystemSettings::GetAppearance().IsDark();
    wxDCPenChanger(dc, wxPen(high));
    if (!(flags & wxCONTROL_DISABLED))
    {
        if (flags & wxCONTROL_PRESSED)
        {
            wxDCBrushChanger(dc, wxBrush(high.ChangeLightness(dark ? 20 : 150)));
            dc.DrawRectangle(rect);
        }
        else if (flags & wxCONTROL_CURRENT)
        {
            // draw an even lighter background for checked item hovers (since
            // the hover background is the same color as the check background)
            wxDCBrushChanger(dc, wxBrush(high.ChangeLightness((dark ? 40 : 170) + ((flags & wxCONTROL_CHECKED) ? 10 : 0))));
            dc.DrawRectangle(rect);
        }
        else if (flags & wxCONTROL_CHECKED)
        {
            // it's important to put this code in an else statement after the
            // hover, otherwise hovers won't draw properly for checked items
            wxDCBrushChanger(dc, wxBrush(high.ChangeLightness(dark ? 40 : 170)));
            dc.DrawRectangle(rect);
        }
    }
}

void wxRendererGeneric::DrawTabControlBackground(wxWindow* WXUNUSED(win), wxDC& dc, const wxRect& rect, int WXUNUSED(flags))
{
    wxColor baseColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
    // the baseColour is too pale to use as our base colour, so darken it a bit --
    if ((255-baseColour.Red()) +
        (255-baseColour.Green()) +
        (255-baseColour.Blue()) < 60)
    {
        baseColour = baseColour.ChangeLightness(92);
    }
    wxColor borderColour = baseColour.ChangeLightness(75);

    // draw background using arbitrary hard-coded, but at least adapted to dark
    // mode, gradient
    int topLightness, bottomLightness;
    if (wxSystemSettings::GetAppearance().IsUsingDarkBackground())
    {
        topLightness = 110;
        bottomLightness = 90;
    }
    else
    {
        topLightness = 90;
        bottomLightness = 170;
    }

    wxColor top_color    = baseColour.ChangeLightness(topLightness);
    wxColor bottom_color = baseColour.ChangeLightness(bottomLightness);
    wxRect r(rect.x, rect.y, rect.width + 2, rect.height - 3);
    dc.GradientFillLinear(r, top_color, bottom_color, wxSOUTH);

    // draw base lines
    wxDCPenChanger(dc, wxPen(borderColour));
    wxDCBrushChanger(dc, wxBrush(baseColour));
    dc.DrawRectangle(0, rect.GetHeight() - 4, rect.GetWidth(), 4);
}

void wxRendererGeneric::DrawTabControlTab(wxWindow* WXUNUSED(win), wxDC& dc, const wxRect& rect, int flags)
{
    wxColor baseColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
    // the baseColour is too pale to use as our base colour, so darken it a bit --
    if ((255-baseColour.Red()) +
        (255-baseColour.Green()) +
        (255-baseColour.Blue()) < 60)
    {
        baseColour = baseColour.ChangeLightness(92);
    }
    wxColor borderColour = baseColour.ChangeLightness(75);

    dc.SetClippingRegion(rect.x, rect.y, rect.width, rect.height - 3);
    // create points that will make the tab outline
    wxPoint border_points[6];
    border_points[0] = wxPoint(rect.x,                  rect.y + rect.height - 4);
    border_points[1] = wxPoint(rect.x,                  rect.y + 2);
    border_points[2] = wxPoint(rect.x + 2,              rect.y);
    border_points[3] = wxPoint(rect.x + rect.width - 2, rect.y);
    border_points[4] = wxPoint(rect.x + rect.width,     rect.y + 2);
    border_points[5] = wxPoint(rect.x + rect.width,     rect.y + rect.height - 4);

    bool isdark = wxSystemSettings::GetAppearance().IsUsingDarkBackground();

    // draw active tab
    if (flags & wxCONTROL_SELECTED)
    {
        // draw base background color
        wxRect r(rect.x, rect.y, rect.width, rect.height);
        {
            wxDCPenChanger(dc, wxPen(baseColour));
            wxDCBrushChanger(dc, wxBrush(baseColour));
            dc.DrawRectangle(r.x + 1, r.y + 1, r.width - 1, r.height - 4);
        }

        // this white helps fill out the gradient at the top of the tab
        wxColor gradient = *wxWHITE;
        if (isdark)
        {
            //dark mode, we go darker
            gradient = baseColour.ChangeLightness(70);
        }

        {
            wxDCPenChanger(dc, wxPen(gradient));
            wxDCBrushChanger(dc, wxBrush(gradient));
            dc.DrawRectangle(r.x + 2, r.y + 1, r.width - 3, r.height - 4);
        }

        // these two points help the rounded corners appear more antialiased
        {
            wxDCPenChanger(dc, wxPen(baseColour));
            dc.DrawPoint(r.x + 2, r.y + 1);
            dc.DrawPoint(r.x + r.width - 2, r.y + 1);
        }

        // set rectangle down a bit for gradient drawing
        r.SetHeight(r.GetHeight() / 2);
        r.x += 2;
        r.width -= 3;
        r.y += r.height;
        r.y -= 2;

        // draw gradient background
        dc.GradientFillLinear(r, baseColour, gradient, wxNORTH);
    }
    // draw inactive tab
    else
    {
        wxRect r(rect.x, rect.y + 1, rect.width, rect.height - 3);

        // start the gradient up a bit and leave the inside border inset
        // by a pixel for a 3D look.  Only the top half of the inactive
        // tab will have a slight gradient
        r.x += 3;
        r.y++;
        r.width -= 4;
        r.height /= 2;
        r.height--;

        // draw top gradient fill for glossy look
        wxColor top_color = baseColour;
        wxColor bottom_color = top_color.ChangeLightness(160);
        if (isdark)
        {
            // dark mode, we go darker
            top_color = baseColour.ChangeLightness(70);
            bottom_color = baseColour;
        }
        dc.GradientFillLinear(r, bottom_color, top_color, wxNORTH);

        r.y += r.height;
        r.y--;

        // draw bottom fill for glossy look
        dc.GradientFillLinear(r, baseColour, baseColour, wxSOUTH);
    }

    // draw tab outline
    wxDCPenChanger(dc, wxPen(borderColour));
    wxDCBrushChanger(dc, *wxTRANSPARENT_BRUSH);
    dc.DrawPolygon(WXSIZEOF(border_points), border_points);

    // there are two horizontal grey lines at the bottom of the tab control,
    // this gets rid of the top one of those lines in the tab control
    if (flags & wxCONTROL_SELECTED)
    {
        wxDCPenChanger(dc, wxPen(baseColour));
        dc.DrawLine(border_points[0].x + 1,
                    border_points[0].y,
                    border_points[5].x,
                    border_points[5].y);
    }
    dc.DestroyClippingRegion();
}

// ----------------------------------------------------------------------------
// A module to allow cleanup of generic renderer.
// ----------------------------------------------------------------------------

class wxGenericRendererModule: public wxModule
{
    wxDECLARE_DYNAMIC_CLASS(wxGenericRendererModule);
public:
    wxGenericRendererModule() {}
    bool OnInit() wxOVERRIDE { return true; }
    void OnExit() wxOVERRIDE { wxRendererGeneric::Cleanup(); }
};

wxIMPLEMENT_DYNAMIC_CLASS(wxGenericRendererModule, wxModule);
