

#include "stdafx.h"
#include "Cbutton.h"
#include "CbuttonDoc.h"
#include "CbuttonView.h"
#include <time.h>
#include<iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDB_ZLH 0

IMPLEMENT_DYNCREATE(CCbuttonView, CView)

BEGIN_MESSAGE_MAP(CCbuttonView, CView)
	//{{AFX_MSG_MAP(CCbuttonView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_MENU_CAPTION, OnMenuCaption)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_OUT, OnMenuOut)
	ON_COMMAND(ID_MACHINE, OnMachine)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()



/******************************************************************************************************************/
/************************************************需要添加的两个函数如下********************************************/
void BFS(int p[30][30], int i, int j, int** record, int n, int m) { //i,j,行数，列数
	if (record[i][j] == -2)return; //如果是雷直接返回
	if (p[i][j] != -1)return;     //如果已经打开了也返回
	if (p[i][j] == -1) {	//如果p没被打开
		p[i][j] = 0;	//后续进行record赋值
		if (record[i][j] != 0)return;
		else
		{
			if (i + 1 < n) {
				BFS(p, i + 1, j, record, n, m);
			}
			if (i - 1 >= 0) {
				BFS(p, i - 1, j, record, n, m);
			}
			if (j + 1 < 20) {
				BFS(p, i, j + 1, record, n, m);
			}
			if (j - 1 >= 0) {
				BFS(p, i, j - 1, record, n, m);
			}
			if (i + 1 < 20 && j + 1 < 20)BFS(p, i + 1, j + 1, record, n, m);
			if (i + 1 < 20 && j - 1 >= 0)BFS(p, i + 1, j - 1, record, n, m);
			if (i - 1 >= 0 && j + 1 < 20)BFS(p, i - 1, j + 1, record, n, m);
			if (i - 1 >= 0 && j - 1 >= 0)BFS(p, i - 1, j - 1, record, n, m);
		}
	}
}
int CCbuttonView::RefreshGamePanel(int GamePanel[30][30], int x, int y, int mine[30][30], int n, int m, int k)
{
	int** record = new int*[n];
	for (int i = 0; i < n; i++) {
		record[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mine[i][j] == 1)record[i][j] = -2; //-2表示该处为雷
			if (mine[i][j] == 0)record[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mine[i][j] == 1) {
				if (i + 1 < n) {
					if (record[i + 1][j] != -2)
						record[i + 1][j]++;
				}
				if (i - 1 >= 0) {
					if (record[i - 1][j] != -2)
						record[i - 1][j]++;
				}
				if (j + 1 < m) {
					if (record[i][j + 1] != -2)
						record[i][j + 1]++;
				}
				if (j - 1 >= 0) {
					if (record[i][j - 1] != -2)
						record[i][j - 1]++;
				}
				if (i + 1 < n && j + 1 < m) {
					if (record[i + 1][j + 1] != -2)
						record[i + 1][j + 1]++;
				}
				if (i + 1 < n && j - 1 >= 0) {
					if (record[i + 1][j - 1] != -2)
						record[i + 1][j - 1]++;
				}
				if (i - 1 >= 0 && j + 1 < m) {
					if (record[i - 1][j + 1] != -2)
						record[i - 1][j + 1]++;
				}
				if (i - 1 >= 0 && j - 1 >= 0) {
					if (record[i - 1][j - 1] != -2)
						record[i - 1][j - 1]++;
				}
			}
		}
	}

	if (GamePanel[x][y] >= 0)return 0;
	if (GamePanel[x][y] == -1) { //如果点击的点是-1，即未打开
		if (record[x][y] == -2) {
			 return -1;
		}
		else {
			BFS(GamePanel, x, y, record, n, m);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (GamePanel[i][j] == 0) {
					GamePanel[i][j] = record[i][j];
				}
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (GamePanel[i][j] == -1)sum++;
		}
	}
	if (sum == k)return 1;
	//请将你封装的RefreshGamePanel函数体添加到此处，并去掉下行的return 0
	for (int i = 0; i < n; i++) {
		delete[] record[i];
	}
	delete[] record;
	return 0;
}
int checkBoom(int **p, int n, int m, int i, int j) {
	int isBoom = 0;
	if (i + 1 < n) {
		if (p[i + 1][j] == -2)isBoom++;
	}
	if (i - 1 >= 0) {
		if (p[i - 1][j] == -2)isBoom++;
	}
	if (j + 1 < m) {
		if (p[i][j + 1] == -2)isBoom++;
	}
	if (j - 1 >= 0) {
		if (p[i][j - 1] == -2)isBoom++;
	}
	if (i + 1 < n&&j + 1 < m) {
		if (p[i + 1][j + 1] == -2)isBoom++;
	}
	if (i + 1 < n&&j - 1 >= 0) {
		if (p[i + 1][j - 1] == -2)isBoom++;
	}
	if (i - 1 >= 0 && j + 1 < m) {
		if (p[i - 1][j + 1] == -2)isBoom++;
	}
	if (i - 1 >= 0 && j - 1 >= 0) {
		if (p[i - 1][j - 1] == -2)isBoom++;
	}
	return isBoom;
}
int checkMaybeBoom(int **p, int n, int m, int i, int j) {
	int MaybeBoom = 0;
	if (i + 1 < n) {
		if (p[i + 1][j] == -1)MaybeBoom++;
	}
	if (i - 1 >= 0) {
		if (p[i - 1][j] == -1)MaybeBoom++;
	}
	if (j + 1 < m) {
		if (p[i][j + 1] == -1)MaybeBoom++;
	}
	if (j - 1 >= 0) {
		if (p[i][j - 1] == -1)MaybeBoom++;
	}
	if (i + 1 < n&&j + 1 < m) {
		if (p[i + 1][j + 1] == -1)MaybeBoom++;
	}
	if (i + 1 < n&&j - 1 >= 0) {
		if (p[i + 1][j - 1] == -1)MaybeBoom++;
	}
	if (i - 1 >= 0 && j + 1 < m) {
		if (p[i - 1][j + 1] == -1)MaybeBoom++;
	}
	if (i - 1 >= 0 && j - 1 >= 0) {
		if (p[i - 1][j - 1] == -1)MaybeBoom++;
	}
	return MaybeBoom++;
}
int checkArroundSecond(int** p, int n, int m, int i, int j, int&tarx, int&tary);
int checkArroundfirst(int** p, int n, int m, int i, int j, int& tarx, int& tary);
void CCbuttonView::machine(int GamePanel[30][30], int n, int m, int &x, int &y)
{
	int ifChange = 1; //是否找到雷
	int **CopyGamePanel = new int*[n];
	for (int i = 0; i < m; i++) {
		CopyGamePanel[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			CopyGamePanel[i][j] = GamePanel[i][j];//把原图copy，以便操作
		}
	}
	while (ifChange)
	{
		ifChange = !ifChange;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (CopyGamePanel[i][j] == -1 || CopyGamePanel[i][j] == 0 || CopyGamePanel[i][j] == -2)continue;
				if (CopyGamePanel[i][j] > 0) {
					int tarx = -1, tary = -1;
					int temp = checkArroundfirst(CopyGamePanel, n, m, i, j, tarx, tary);
					if (temp == 1) ifChange = 1; //若找到雷，则重新再看图
					if (temp == 2) {
						x = tarx; y = tary;
						for (int i = 0; i < n; i++) {
							delete[] CopyGamePanel[i];
						}
						delete[] CopyGamePanel; return;
					}
					if (temp == 0)continue;
				}
			}
		}
		if (ifChange == 0) { //若到最后也没有发现雷且没有找到可能的点，说明初级策略失效
			//使用高级策略再找一遍

			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					int tarx = -1, tary = -1;
					int temp = checkArroundSecond(CopyGamePanel, n, m, i, j, tarx, tary);
					if (temp == 1) ifChange = 1; //若找到雷，则重新再看图
					if (temp == 2) {
						x = tarx; y = tary;
						for (int i = 0; i < n; i++) {
							delete[] CopyGamePanel[i];
						}
						delete[] CopyGamePanel; return;
					}
					if (temp == 0)continue;
				}
			}
		}
	}
	//若需要随机取一个
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//			if ((GamePanel[i][j] == -1) && (CopyGamePanel[i][j] != -2)) {
			if (CopyGamePanel[i][j] == -1) {
				x = i; y = j;  return;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] CopyGamePanel[i];
	}
	delete[] CopyGamePanel;
}
int checkArroundSecond(int** p, int n, int m, int i, int j, int& tarx, int& tary) {
	if (p[i][j] <= 0)return 0;
	int ifchange = 0;
	if (i + 1 < n && p[i + 1][j] > 0) {
		int thisBoom = p[i][j] - checkBoom(p, n, m, i, j);	int unsameplacethat = 0; int unsameplacethis = 0;
		int thatBoom = p[i + 1][j] - checkBoom(p, n, m, i + 1, j);
		if (i - 1 >= 0 && j - 1 >= 0) {
			if (p[i - 1][j - 1] == -1)unsameplacethis++;
		}
		if (i - 1 >= 0) {
			if (p[i - 1][j] == -1)unsameplacethis++;
		}
		if (i - 1 >= 0 && j + 1 < m) {
			if (p[i - 1][j + 1] == -1)unsameplacethis++;
		}
		if (i + 2 < n&&j - 1 >= 0) {
			if (p[i + 2][j - 1] == -1)unsameplacethat++;
		}
		if (i + 2 < n) {
			if (p[i + 2][j] == -1)unsameplacethat++;
		}
		if (i + 2 < n&&j + 1 < m) {
			if (p[i + 2][j + 1] == -1)unsameplacethat++;
		}
		if ((thisBoom - thatBoom) == unsameplacethis && unsameplacethis > 0) { //如果非公共区域与雷的差数相同，则非公共区域全为雷
			if (i - 1 >= 0 && j - 1 >= 0) {
				if (p[i - 1][j - 1] == -1)p[i - 1][j - 1] = -2; ifchange = 1;
			}
			if (i - 1 >= 0) {
				if (p[i - 1][j] == -1)p[i - 1][j] = -2; ifchange = 1;
			}
			if (i - 1 >= 0 && j + 1 < m) {
				if (p[i - 1][j + 1] == -1)p[i - 1][j + 1] = -2; ifchange = 1;
			}
		}
		if (ifchange == 1)return 1;
		if (unsameplacethis == 0 && thisBoom == thatBoom) {//则另一边都可打开
			if (i + 2 < n&&j - 1 >= 0) {
				if (p[i + 2][j - 1] == -1) {
					tarx = i + 2; tary = j - 1; return 2;
				}
			}
			if (i + 2 < n) {
				if (p[i + 2][j] == -1) {
					tarx = i + 2; tary = j; return 2;
				}
			}
			if (i + 2 < n&&j + 1 < m) {
				if (p[i + 2][j + 1] == -1) {
					tarx = i + 2; tary = j + 1; return 2;
				}
			}
		}

	}
	if (j + 1 < m&&p[i][j + 1] > 0) {
		int thisBoom = p[i][j] - checkBoom(p, n, m, i, j);	int unsameplacethat = 0; int unsameplacethis = 0;
		int thatBoom = p[i][j + 1] - checkBoom(p, n, m, i, j + 1);
		if (j - 1 >= 0 && i - 1 >= 0) {
			if (p[i - 1][j - 1] == -1)unsameplacethis++;
		}
		if (j - 1 >= 0 && i + 1 < n) {
			if (p[i + 1][j - 1] == -1)unsameplacethis++;
		}
		if (j - 1 >= 0) {
			if (p[i][j - 1] == -1)unsameplacethis++;
		}
		if (i - 1 >= 0 && j + 2 < m) {
			if (p[i - 1][j + 2] == -1)unsameplacethat++;
		}
		if (i + 1 < n&&j + 2 < m) {
			if (p[i + 1][j + 2] == -1)unsameplacethat++;
		}
		if (j + 2 < m) {
			if (p[i][j + 2] == -1)unsameplacethat++;
		}
		if ((thisBoom - thatBoom) == unsameplacethis && unsameplacethis > 0) {//若雷差为i,j的非公共区，则该非公共区都是雷
			if (j - 1 >= 0 && i - 1 >= 0) {
				if (p[i - 1][j - 1] == -1)p[i - 1][j - 1] = -2; ifchange = 1;
			}
			if (j - 1 >= 0 && i + 1 < n) {
				if (p[i + 1][j - 1] == -1)p[i + 1][j - 1] = -2; ifchange = 1;
			}
			if (j - 1 >= 0) {
				if (p[i][j - 1] == -1)p[i][j - 1] = -2; ifchange = 1;
			}
		}
		if (ifchange == 1)return 1;
		if (unsameplacethis == 0 && thisBoom == thatBoom) {//则另一边都可打开
			if (i - 1 >= 0 && j + 2 < m) {
				if (p[i - 1][j + 2] == -1) {
					tarx = i - 1; tary = j + 2; return 2;
				}
			}
			if (i + 1 < n&&j + 2 < m) {
				if (p[i + 1][j + 2] == -1) {
					tarx = i + 1; tary = j + 2; return 2;
				}
			}
			if (j + 2 < m) {
				if (p[i][j + 2] == -1) {
					tarx = i; tary = j + 2; return 2;
				}
			}
		}
	}
	return 0;
}
int checkArroundfirst(int** p, int n, int m, int i, int j, int& tarx, int& tary) {
	int isBoom = 0;
	int maybeBoom = 0;  //可能是炸弹的数量
	isBoom = checkBoom(p, n, m, i, j);
	maybeBoom = checkMaybeBoom(p, n, m, i, j);
	if (isBoom == p[i][j]) { //若周围的boom个数和所示相同，即可随便打开周围未打开的格子
		if (i + 1 < n) {
			if (p[i + 1][j] == -1) {
				tarx = i + 1; tary = j; return 2;   //表示找到可以打开的点
			}
		}
		if (i - 1 >= 0) {
			if (p[i - 1][j] == -1) {
				tarx = i - 1; tary = j; return 2;
			}
		}
		if (j + 1 < m) {
			if (p[i][j + 1] == -1) {
				tarx = i; tary = j + 1; return 2;
			}
		}
		if (j - 1 >= 0) {
			if (p[i][j - 1] == -1) {
				tarx = i; tary = j - 1; return 2;
			}
		}
		if (i + 1 < n&&j + 1 < m) {
			if (p[i + 1][j + 1] == -1) {
				tarx = i + 1; tary = j + 1; return 2;
			}
		}
		if (i + 1 < n&&j - 1 >= 0) {
			if (p[i + 1][j - 1] == -1) {
				tarx = i + 1; tary = j - 1; return 2;
			}
		}
		if (i - 1 >= 0 && j + 1 < m) {
			if (p[i - 1][j + 1] == -1) {
				tarx = i - 1; tary = j + 1; return 2;
			}
		}
		if (i - 1 >= 0 && j - 1 >= 0) {
			if (p[i - 1][j - 1] == -1) {
				tarx = i - 1; tary = j - 1; return 2;
			}
		}
	}
	if ((maybeBoom + isBoom) == p[i][j]) { //若没打开的+是boom的个数与总共boom个数相同，即没打开的是boom
		int changed = 0;
		if (i + 1 < n) {
			if (p[i + 1][j] == -1) {
				p[i + 1][j] = -2; //-2表示boom
				changed = 1;
			}
		}
		if (i - 1 >= 0) {
			if (p[i - 1][j] == -1) {
				p[i - 1][j] = -2;
				changed = 1;
			}
		}
		if (j + 1 < m) {
			if (p[i][j + 1] == -1) {
				p[i][j + 1] = -2;
				changed = 1;
			}
		}
		if (j - 1 >= m) {
			if (p[i][j - 1] == -1) {
				p[i][j - 1] = -2;
				changed = 1;
			}
		}
		if (i + 1 < n&&j + 1 < m) {
			if (p[i + 1][j + 1] == -1) { p[i + 1][j + 1] = -2; changed = 1; }
		}
		if (i + 1 < n&&j - 1 >= 0) {
			if (p[i + 1][j - 1] == -1) { p[i + 1][j - 1] = -2; changed = 1; }

		}
		if (i - 1 >= 0 && j + 1 < m) {
			if (p[i - 1][j + 1] == -1) { p[i - 1][j + 1] = -2; changed = 1; }

		}
		if (i - 1 >= 0 && j - 1 >= 0) {
			if (p[i - 1][j - 1] == -1) { p[i - 1][j - 1] = -2; changed = 1; }
		}
		if (changed == 1)
			return 1;
	}
	return 0;
}


/************************************************需要添加的两个函数如上********************************************/
/******************************************************************************************************************/
















/*************************************以下代码不用管********************************************/
CCbuttonView::CCbuttonView()
{

	// TODO: add construction code here
	srand(int(time(0)));
	minenum=50;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
		{	
			mine[i][j]=0;
			GamePanel[i][j]=-1;
		}

	for(int k=0;k<minenum;k++)
	{
		i=rand()%20;
		j=rand()%20;
		while(mine[i][j]!=0)
		{
			i=rand()%20;
			j=rand()%20;
		}
		mine[i][j]=1;
	}
	x=0;y=0;
	id=0;
	i=0;j=0;
	showmine=-1;
	win=0;
	current_j=-1;
	current_i=-1;
}

CCbuttonView::~CCbuttonView()
{
}


void CCbuttonView::OnMenuNew() 
{
	// TODO: Add your command handler code here
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
		{	
			mine[i][j]=0;
			GamePanel[i][j]=-1;
			::ShowWindow(cbutton[i][j],SW_SHOW);
		}
		
		for(int k=0;k<minenum;k++)
		{
			i=rand()%20;
			j=rand()%20;
			while(mine[i][j]!=0)
			{
				i=rand()%20;
				j=rand()%20;
			}
			mine[i][j]=1;
		}
		x=0;y=0;
		id=0;
		i=0;j=0;
		win=0;
		showmine=-1;
		current_i=-1;
		current_j=-1;
		CRect rect1;
		GetClientRect(&rect1);
		InvalidateRect(rect1);

}
void CCbuttonView::OnMenuOut() 
{
	// TODO: Add your command handler code here
	 
	//PostQuitMessage(0);
	exit(0) ;
}


BOOL CCbuttonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView drawing

void CCbuttonView::OnDraw(CDC* pDC)
{
	CCbuttonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView printing

BOOL CCbuttonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCbuttonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCbuttonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView diagnostics

#ifdef _DEBUG
void CCbuttonView::AssertValid() const
{
	CView::AssertValid();
}

void CCbuttonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCbuttonDoc* CCbuttonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCbuttonDoc)));
	return (CCbuttonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView message handlers

int CCbuttonView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	id = 0;
	x=0;y=0;
	int realid;
	for(i=0;i<20;i++)
	 {
		 for(j=0;j<20;j++)
		 {
			 if (id == 0) realid = 1;
			 else realid = id;
			  cbutton[i][j].Create("",WS_CHILD | WS_VISIBLE,CRect(x,y,x+20,y+20),this,realid);
			  x+=20;
			  id+=20;
		 }
		 x=0;
		 y+=20;
	 }
     return 0;
}

void CCbuttonView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	
	CView::OnLButtonDown(nFlags, point);
}


void CCbuttonView::OnRButtonDown(UINT nFlags, CPoint point)			 
{
	// TODO: Add your message handler code here and/or call default
	/*for(int k=0;k<20;k++)
	{
	  ::ShowWindow(cbutton[i_lei[k]][j_lei[k]],SW_HIDE);
	}*/
	showmine*=-1;
		CClientDC dc(this);
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_LEI);
	if(showmine==1)
	{
	
		CBrush brush(&bitmap);
		//cbutton[0][0].SetBitmap();
		//dc.FillRect(CRect(point.x,point.y,point.x+20,point.y+20),&brush);
		
		for(i=0;i<20;i++)
		{
			 for(j=0;j<20;j++)
			 {
				 if(mine[i][j]==1)
				 {
					 dc.FillRect(CRect(j*20,i*20,j*20+20,i*20+20),&brush);
				 }
			 }
		}
	}
	else{
	
		CRect rect1;
		GetClientRect(&rect1);
		InvalidateRect(rect1);
	}
	//cbutton[0][0].SetBitmap(bitmap);

	CView::OnRButtonDown(nFlags, point);
}

void CCbuttonView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
    CBrush brush(RGB(255,255,255));
	dc.SelectObject(&brush);
	dc.FillRect(CRect(0,0,800,600),&brush);

	CPen pen(PS_SOLID,1,RGB(180,180,180));
 
	for( i=0;i<420;i+=20)
	{
		dc.SelectObject(&pen);
		dc.MoveTo(i,0);
		dc.LineTo(i,440);
		dc.MoveTo(0,i);
		dc.LineTo(400,i);
	}
				
    COLORREF col=dc.SetBkColor(RGB(255,255,255));
	dc.SetTextColor(RGB(0,0,255));

	if(win==0)
	{

		for(i=0;i<20;i++)
            for(j=0;j<20;j++)
			{
				if(GamePanel[i][j]==0)
					::ShowWindow(cbutton[i][j],SW_HIDE);
				else if(GamePanel[i][j]>0 && GamePanel[i][j]<9)
				{
					::ShowWindow(cbutton[i][j],SW_HIDE);
					str.Format("%d",GamePanel[i][j]);
					dc.SetTextColor(RGB(0,0,255));
					dc.DrawText(str,CRect(j*20,i*20,j*20+20,i*20+20),DT_CENTER);
				}
			}
	}
	else if(win==-1 || win==1)
	{
		
		for(i=0;i<20;i++)
            for(j=0;j<20;j++)
			{
				if(GamePanel[i][j]==0)
					::ShowWindow(cbutton[i][j],SW_HIDE);
				else if(GamePanel[i][j]>0 && GamePanel[i][j]<9)
				{
					::ShowWindow(cbutton[i][j],SW_HIDE);
					str.Format("%d",GamePanel[i][j]);
					dc.SetTextColor(RGB(0,0,255));
					dc.DrawText(str,CRect(j*20,i*20,j*20+20,i*20+20),DT_CENTER);
				}
				CBitmap bitmap,bitmap1;
				bitmap.LoadBitmap(IDB_BITMAP_LEI);
				CBrush brush(&bitmap);
		
				if(mine[i][j]==1)
				{
					::ShowWindow(cbutton[i][j],SW_HIDE);
					
					if(win==-1 && current_i==i && current_j==j)
					{
						bitmap1.LoadBitmap(IDB_REDMINE_BITMAP);
						CBrush brush1(&bitmap1);
						dc.FillRect(CRect(j*20,i*20,j*20+20,i*20+20),&brush1);
					}
					else dc.FillRect(CRect(j*20,i*20,j*20+20,i*20+20),&brush);

				}

			}
	}
	// Do not call CView::OnPaint() for painting messages
}


void CCbuttonView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CCbuttonView::OnMenuCaption() 
{
	// TODO: Add your command handler code here

  MessageBox("简易版扫雷游戏图形界面框架","扫雷");
}


BOOL CCbuttonView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
    
	int ii,jj,k,ButtonCmdId=LOWORD(wParam);
	if (ButtonCmdId == 1)
	{
		ii = 0;
		jj = 0;
	}
	else
	{
		ii = (ButtonCmdId / 400);
		jj = (ButtonCmdId - 400 * ii) / 20;
	}

		/************************************************************************/
		/***/ win=RefreshGamePanel(GamePanel,ii,jj,mine,20,20,minenum); /********/
        /************************************************************************/

		CRect rect1;
		GetClientRect(&rect1);
		current_j=jj;
		current_i=ii;
		
		if(win==-1 || win==1)
		{
			InvalidateRect(rect1);
		
			if(win==-1)
				MessageBox("你输了！点击确定重新开始","扫雷",MB_ICONEXCLAMATION);
			else MessageBox("恭喜，你赢了！点击确定重新开始","扫雷",MB_ICONINFORMATION);
			for(i=0;i<20;i++)
				for(j=0;j<20;j++)
				{	
					mine[i][j]=0;
					GamePanel[i][j]=-1;
					::ShowWindow(cbutton[i][j],SW_SHOW);
				}
			
			for(int k=0;k<minenum;k++)
			{
				i=rand()%20;
				j=rand()%20;
				while(mine[i][j]!=0)
				{
					i=rand()%20;
					j=rand()%20;
				}
				mine[i][j]=1;
			}
			x=0;y=0;
			id=0;
			i=0;j=0;
			win=0;
			showmine=-1;
			current_i=-1;
			current_j=-1;
			machinestart=false;
		}
		//InvalidateRect(rect1);
		{
			CClientDC dc(this); // device context for painting
			for(i=0;i<20;i++)
				for(j=0;j<20;j++)
				{
					if(GamePanel[i][j]==0)
						::ShowWindow(cbutton[i][j],SW_HIDE);
					else if(GamePanel[i][j]>0 && GamePanel[i][j]<9)
					{
						::ShowWindow(cbutton[i][j],SW_HIDE);
						str.Format("%d",GamePanel[i][j]);
						dc.SetTextColor(RGB(0,0,255));
						dc.DrawText(str,CRect(j*20,i*20,j*20+20,i*20+20),DT_CENTER);
					}
				}
			
		}
	
	return CView::OnCommand(wParam, lParam);
}

void CCbuttonView::OnMachine() 
{
	// TODO: Add your command handler code here
	int x=-1,y=-1;
	machinestart=true;
	int tim=50,count=0;
	while(machinestart && count<400)
	{
		/*************************************************/
		/*********/machine(GamePanel,20,20, x,y);/********/
		/*************************************************/
		if (x<0 || x>19 || y<0 || y>19) break;
		count++;
		SendMessage(WM_COMMAND,MAKEWPARAM(x*400+20*y,BN_CLICKED),0); 
		Sleep(tim);
	}
}