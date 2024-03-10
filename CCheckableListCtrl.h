#pragma once

#include <vector>
#include <map>
#include <set>

class CCheckableListCtrl : public CListCtrl
{
    DECLARE_DYNAMIC(CCheckableListCtrl)

public:
    CCheckableListCtrl();
    virtual ~CCheckableListCtrl();

    bool IsItemExpandable(int nItem);
    void AddExpandableItem(int parentIndex, const std::vector<CString>& childItems);
    void ToggleChildRows(int nItem);

protected:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);

public:
    int checkboxSize = 15;
    int checkboxGap = 5;
    std::vector<std::pair<bool, bool>> m_checkboxStates;

    std::map<int, std::vector<CString>> m_ExpandableItems; // Maps parent items to their child rows
    std::map<int, bool> m_ExpandedItems; // Keeps track of expanded/collapsed state

    DECLARE_MESSAGE_MAP()
};

