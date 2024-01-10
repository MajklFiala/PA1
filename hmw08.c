#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCell
{
  struct TCell             * m_Right;
  struct TCell             * m_Down;
  int                        m_Row;
  int                        m_Col;
  int                        m_Data;
} TCELL;

typedef struct TRowCol
{
  struct TRowCol           * m_Next;
  TCELL                    * m_Cells;
  int                        m_Idx;
} TROWCOL;

typedef struct TSparseMatrix
{
  TROWCOL                  * m_Rows;
  TROWCOL                  * m_Cols;
} TSPARSEMATRIX;
#endif /* __PROGTEST__ */

void initMatrix   ( TSPARSEMATRIX   * m )
{
  m->m_Rows = nullptr;
  m->m_Cols = nullptr;
}

void addSetCell   ( TSPARSEMATRIX   * m, int rowIdx,int  colIdx,int  data ) 
{

}

bool removeCell   ( TSPARSEMATRIX   * m,int rowIdx,int colIdx )
{

}

void freeMatrix   ( TSPARSEMATRIX   * m )
{
    
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TSPARSEMATRIX  m;
  initMatrix ( &m );
  addSetCell ( &m, 0, 1, 10 );
  addSetCell ( &m, 1, 0, 20 );
  addSetCell ( &m, 1, 5, 30 );
  addSetCell ( &m, 2, 1, 40 );

  
  assert ( m . m_Rows
           && m . m_Rows -> m_Idx == 0
           && m . m_Rows -> m_Cells
           && m . m_Rows -> m_Cells -> m_Row == 0
           && m . m_Rows -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Cells -> m_Data == 10
           && m . m_Rows -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next
           && m . m_Rows -> m_Next -> m_Idx == 1
           && m . m_Rows -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Col == 0
           && m . m_Rows -> m_Next -> m_Cells -> m_Data == 20
           && m . m_Rows -> m_Next -> m_Cells -> m_Right
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Col == 5
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Data == 30
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Idx == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Cols
           && m . m_Cols -> m_Idx == 0
           && m . m_Cols -> m_Cells
           && m . m_Cols -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Cells -> m_Col == 0
           && m . m_Cols -> m_Cells -> m_Data == 20
           && m . m_Cols -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next
           && m . m_Cols -> m_Next -> m_Idx == 1
           && m . m_Cols -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Cells -> m_Row == 0
           && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Data == 10
           && m . m_Cols -> m_Next -> m_Cells -> m_Down
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Row == 2
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Data == 40
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells -> m_Down );
  addSetCell ( &m, 230, 190, 50 );
  assert ( m . m_Rows
           && m . m_Rows -> m_Idx == 0
           && m . m_Rows -> m_Cells
           && m . m_Rows -> m_Cells -> m_Row == 0
           && m . m_Rows -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Cells -> m_Data == 10
           && m . m_Rows -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next
           && m . m_Rows -> m_Next -> m_Idx == 1
           && m . m_Rows -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Col == 0
           && m . m_Rows -> m_Next -> m_Cells -> m_Data == 20
           && m . m_Rows -> m_Next -> m_Cells -> m_Right
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Col == 5
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Data == 30
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Idx == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Idx == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Cols
           && m . m_Cols -> m_Idx == 0
           && m . m_Cols -> m_Cells
           && m . m_Cols -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Cells -> m_Col == 0
           && m . m_Cols -> m_Cells -> m_Data == 20
           && m . m_Cols -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next
           && m . m_Cols -> m_Next -> m_Idx == 1
           && m . m_Cols -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Cells -> m_Row == 0
           && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Data == 10
           && m . m_Cols -> m_Next -> m_Cells -> m_Down
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Row == 2
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Data == 40
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Idx == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells -> m_Down );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells );
  assert ( removeCell ( &m, 0, 1 ) );
  assert ( !removeCell ( &m, 0, 1 ) );
  assert ( !removeCell ( &m, 1, 2 ) );
  assert ( m . m_Rows
           && m . m_Rows -> m_Idx == 1
           && m . m_Rows -> m_Cells
           && m . m_Rows -> m_Cells -> m_Row == 1
           && m . m_Rows -> m_Cells -> m_Col == 0
           && m . m_Rows -> m_Cells -> m_Data == 20
           && m . m_Rows -> m_Cells -> m_Right
           && m . m_Rows -> m_Cells -> m_Right -> m_Row == 1
           && m . m_Rows -> m_Cells -> m_Right -> m_Col == 5
           && m . m_Rows -> m_Cells -> m_Right -> m_Data == 30
           && m . m_Rows -> m_Cells -> m_Right -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next
           && m . m_Rows -> m_Next -> m_Idx == 2
           && m . m_Rows -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Rows -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Rows -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Idx == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Cols
           && m . m_Cols -> m_Idx == 0
           && m . m_Cols -> m_Cells
           && m . m_Cols -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Cells -> m_Col == 0
           && m . m_Cols -> m_Cells -> m_Data == 20
           && m . m_Cols -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next
           && m . m_Cols -> m_Next -> m_Idx == 1
           && m . m_Cols -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Cols -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Idx == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Cells );
  assert ( m . m_Rows -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells );
  freeMatrix ( &m );
  
  

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */