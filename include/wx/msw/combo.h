/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/combo.h
// Purpose:     wxComboCtrl class
// Author:      Jaakko Salli
// Modified by:
// Created:     Apr-30-2006
// Copyright:   (c) Jaakko Salli
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_COMBOCONTROL_H_
#define _WX_COMBOCONTROL_H_

// NB: Definition of _WX_COMBOCONTROL_H_ is used in wx/generic/combo.h to
//     determine whether there is native wxComboCtrl, so make sure you
//     use it in all native wxComboCtrls.

#if wxUSE_COMBOCTRL

#if wxUSE_TIMER
    #include "wx/timer.h"
    #define wxUSE_COMBOCTRL_POPUP_ANIMATION     1
#endif


// ----------------------------------------------------------------------------
// Native wxComboCtrl
// ----------------------------------------------------------------------------

// Define this only if native implementation includes all features
#define wxCOMBOCONTROL_FULLY_FEATURED

extern WXDLLIMPEXP_DATA_CORE(const char) wxComboBoxNameStr[];

class WXDLLIMPEXP_CORE wxComboCtrl : public wxComboCtrlBase
{
public:
    // ctors and such
    wxComboCtrl() : wxComboCtrlBase() { Init(); }

    wxComboCtrl(wxWindow *parent,
                   wxWindowID id = wxID_ANY,
                   const wxString& value = wxEmptyString,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxASCII_STR(wxComboBoxNameStr))
        : wxComboCtrlBase()
    {
        Init();

        (void)Create(parent, id, value, pos, size, style, validator, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxString& value = wxEmptyString,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator = wxDefaultValidator,
                const wxString& name = wxASCII_STR(wxComboBoxNameStr));

    virtual ~wxComboCtrl();

    virtual void PrepareBackground( wxDC& dc, const wxRect& rect, int flags ) const wxOVERRIDE;
    virtual bool IsKeyPopupToggle(const wxKeyEvent& event) const wxOVERRIDE;

    static int GetFeatures() { return wxComboCtrlFeatures::All; }

#if wxUSE_COMBOCTRL_POPUP_ANIMATION
    void OnTimerEvent(wxTimerEvent& WXUNUSED(event)) { DoTimerEvent(); }

protected:
    void DoTimerEvent();

    virtual bool AnimateShow( const wxRect& rect, int flags ) wxOVERRIDE;
#endif // wxUSE_COMBOCTRL_POPUP_ANIMATION

protected:

    // Dummy method - we override all functions that call this
    virtual WXHWND GetEditHWND() const wxOVERRIDE { return NULL; }

    // Virtual method to allow a custom representation of the
    // PaintTextArea while no popup is open.
    virtual void PaintTextArea(wxDC& dc, const wxRect& rect);

    // customization
    virtual void OnResize() wxOVERRIDE;
    virtual wxCoord GetNativeTextIndent() const wxOVERRIDE;

    // event handlers
    void OnPaintEvent( wxPaintEvent& event );
    void OnMouseEvent( wxMouseEvent& event );

    virtual bool HasTransparentBackground() wxOVERRIDE { return IsDoubleBuffered(); }

private:
    void Init();

#if wxUSE_COMBOCTRL_POPUP_ANIMATION
    // Popup animation related
    wxMilliClock_t m_animStart;
    wxTimer     m_animTimer;
    wxRect      m_animRect;
    int         m_animFlags;
#endif

    wxDECLARE_EVENT_TABLE();

    wxDECLARE_DYNAMIC_CLASS(wxComboCtrl);
};


#endif // wxUSE_COMBOCTRL
#endif
    // _WX_COMBOCONTROL_H_
