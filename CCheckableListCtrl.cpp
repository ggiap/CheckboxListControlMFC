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
    ON_NOTIFY_REFLECT(NM_CLICK, OnNMClick)
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

void CCheckableListCtrl::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // Retrieve the mouse click position
    CPoint clickPoint = pNMItemActivate->ptAction;

    // Perform a hit test to find out where the list was clicked
    LVHITTESTINFO hitTestInfo;
    hitTestInfo.pt = clickPoint;
    HitTest(&hitTestInfo);

    if (hitTestInfo.iItem != -1)
    {
        // Calculate the icon's position based on the control's width and the icon's size
        const int iconSize = 16; // Icon size
        const int marginRight = 180; // Margin from the right edge of the control

        CRect rcList;
        GetClientRect(&rcList);
        int listWidth = rcList.Width();

        int iconX = listWidth - iconSize - marginRight;
        int iconY = hitTestInfo.iItem; // Placeholder for actual Y position calculation

        RECT itemRect;
        GetItemRect(hitTestInfo.iItem, &itemRect, LVIR_BOUNDS);
        int iconYTop = itemRect.top + (itemRect.bottom - itemRect.top - iconSize) / 2;
        int iconYBottom = iconYTop + iconSize;

        // Check if the click was within the icon's bounds
        if (clickPoint.x >= iconX && clickPoint.x <= (iconX + iconSize) &&
            clickPoint.y >= iconYTop && clickPoint.y <= iconYBottom)
        {
            // The click was on the icon, toggle expansion
            if (IsItemExpandable(hitTestInfo.iItem))
            {
                ToggleChildRows(hitTestInfo.iItem);
            }
        }
    }
}

bool CCheckableListCtrl::IsItemExpandable(int nItem)
{
    return m_ExpandableItems.find(nItem) != m_ExpandableItems.end();
}

void CCheckableListCtrl::AddExpandableItem(int parentIndex, const std::vector<CString>& childItems)
{
    // Store child items for the parent index
    m_ExpandableItems[parentIndex] = childItems;
    // Initially, parents are not expanded
    m_ExpandedItems[parentIndex] = false;
}

void CCheckableListCtrl::ToggleChildRows(int nItem)
{
    auto it = m_ExpandedItems.find(nItem);
    if (it != m_ExpandedItems.end())
    {
        bool isExpanded = it->second;
        auto children = m_ExpandableItems[nItem];

        if (isExpanded)
        {
            // Collapse: Remove child items
            for (size_t i = 0; i < children.size(); ++i)
            {
                DeleteItem(nItem + 1); // Assuming children are directly below the parent
            }
        }
        else
        {
            // Expand: Add child items
            for (size_t i = 0; i < children.size(); ++i)
            {
                InsertItem(LVIF_TEXT, nItem + 1 + i, children[i], 0, 0, 0, 0);
            }
        }
        // Toggle expanded state
        m_ExpandedItems[nItem] = !isExpanded;
    }
}