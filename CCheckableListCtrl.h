#pragma once

#include <vector>

class CCheckableListCtrl : public CListCtrl
{
    DECLARE_DYNAMIC(CCheckableListCtrl)

public:
    CCheckableListCtrl();
    virtual ~CCheckableListCtrl();

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
    int checkboxSize = 15;
    int checkboxGap = 5;
    std::vector<std::pair<bool, bool>> m_checkboxStates;
};

