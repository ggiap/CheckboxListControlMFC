#include "pch.h"
#include "CCheckableListCtrl.h"

IMPLEMENT_DYNAMIC(CCheckableListCtrl, CListCtrl)

CCheckableListCtrl::CCheckableListCtrl()
{
}

CCheckableListCtrl::~CCheckableListCtrl()
{
}

BEGIN_MESSAGE_MAP(CCheckableListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CCheckableListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Perform hit testing to find the item under the cursor
    LVHITTESTINFO hitTestInfo = { 0 };
    hitTestInfo.pt = point;
    int itemIndex = this->HitTest(&hitTestInfo);

    // If an item was hit, determine if the click was on one of our custom checkboxes
    if (itemIndex != -1)
    {
        // Obtain the item's rectangle
        CRect itemRect;
        this->GetItemRect(itemIndex, &itemRect, LVIR_BOUNDS);

        // Calculate the checkbox rectangles based on the itemRect
        CRect checkboxRect1(itemRect.left + 5, itemRect.top + (itemRect.Height() - checkboxSize) / 2, itemRect.left + 5 + checkboxSize, itemRect.top + (itemRect.Height() + checkboxSize) / 2);
        CRect checkboxRect2 = checkboxRect1;
        checkboxRect2.OffsetRect(checkboxSize + 5, 0); // Position the second checkbox

        // Check if the click was within the bounds of either checkbox
        if (checkboxRect1.PtInRect(point))
        {
            // Toggle the state of the first checkbox for this item
            m_checkboxStates[itemIndex].first = !m_checkboxStates[itemIndex].first;
            this->InvalidateRect(itemRect); // Invalidate the item area to trigger a redraw
        }
        else if (checkboxRect2.PtInRect(point))
        {
            // Toggle the state of the second checkbox for this item
            m_checkboxStates[itemIndex].second = !m_checkboxStates[itemIndex].second;
            this->InvalidateRect(itemRect); // Invalidate the item area to trigger a redraw
        }
    }

    // Call the parent class's OnLButtonDown in case it has important logic
    CListCtrl::OnLButtonDown(nFlags, point);
}
