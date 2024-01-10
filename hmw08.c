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
    TCELL *new_cell = (TCELL*)malloc(sizeof(*new_cell));
  new_cell->m_Row = rowIdx;
  new_cell->m_Col = colIdx;
  new_cell->m_Data = data;

  //create colums linked list struct TROWCOL

  TROWCOL *col = (TROWCOL*)malloc(sizeof(*col));
  col->m_Idx = colIdx;

  TROWCOL *cols = m->m_Cols;
  

  //if there is no colums linked list or there is then go through it
  if(cols == nullptr){
    col->m_Next = nullptr;
    new_cell->m_Down = nullptr;
    new_cell->m_Right = nullptr;
    col->m_Cells = new_cell;
    m->m_Cols = col;
  }else{
    TROWCOL *col_prev = nullptr;
  TCELL *cell_prev = nullptr;

  //going through the colum linked list 
  while(cols != nullptr){
    if(cols->m_Idx == colIdx){
      //going through the cell linked list in the specific column
      TCELL *cell = cols->m_Cells;
      while(cell != nullptr){
        //check if the row and col already exists and only change the data
        if(cell->m_Row == rowIdx){
          cell->m_Data = data;
          break;
        }else if(cell->m_Row <  rowIdx){
          if(cell->m_Down == nullptr){
            new_cell->m_Down = nullptr;
            cell->m_Down = new_cell;
            break;
          }
          cell_prev = cell;
        }else if(cell->m_Row > rowIdx){
          new_cell->m_Down = cell;
          if(cell_prev != nullptr){
            cell_prev->m_Down = new_cell;
          }else{
            cols->m_Cells = new_cell;
          }
          break;
        }
        cell = cell->m_Down;
        
      }
      free(col);
      break;
    }else if(cols->m_Idx < colIdx){
      if(cols->m_Next == nullptr){
        new_cell->m_Down = nullptr;
        col->m_Cells = new_cell;
        col->m_Next = nullptr;
        cols->m_Next = col;
        break;
      }
      col_prev = cols;
    }else if(cols->m_Idx > colIdx){
      new_cell->m_Down = nullptr;
      col->m_Cells = new_cell;
      col->m_Next = cols;
      if(col_prev != nullptr){
        col_prev->m_Next = col;
      }else{
        m->m_Cols = col;
      }
      break;
    }
    cols = cols->m_Next;
  }
  }

  //creates the row linke dlist for struct TROWCOL
  TROWCOL *row = (TROWCOL*)malloc(sizeof(*row));
  row->m_Idx = rowIdx;


  TROWCOL *rows = m->m_Rows;

  //if row list exists or not
  if(rows == nullptr){
    row->m_Next = nullptr;
    row->m_Cells = new_cell;
    m->m_Rows = row;
  }else{
    TROWCOL *row_prev = nullptr;
    TCELL *cell_prev2 = nullptr;

    //loop through the row list
    while(rows != nullptr){
      if(rows->m_Idx == rowIdx){
          //loop through the cell list iin the specisif row list
          TCELL *cell2 =rows->m_Cells;
          while(cell2 != nullptr){
            if(cell2->m_Col == colIdx){
              cell2->m_Data = data;
              free(new_cell);
              break;
            }else if(cell2->m_Col < colIdx){
              if(cell2->m_Right == nullptr){
                new_cell->m_Right = nullptr;
                cell2->m_Right = new_cell;
                break;
              }
              cell_prev2 = cell2;
            }else if(cell2->m_Col > colIdx){
              new_cell->m_Right = cell2;
              if(cell_prev2 != nullptr){
                cell_prev2->m_Right = new_cell;
              }else{
                rows->m_Cells = new_cell;
              }
              break;
            }
            cell2 = cell2->m_Right;
          }
          free(row);
        break;

      }else if(rows->m_Idx < rowIdx){
        if(rows->m_Next == nullptr){
          new_cell->m_Right = nullptr;
          row->m_Cells = new_cell;
          row->m_Next = nullptr;
          rows->m_Next = row;
          break;
        }
        row_prev = rows;
      }else if(rows->m_Idx > rowIdx){
        new_cell->m_Right = nullptr;
        row->m_Cells = new_cell;
        row->m_Next = rows;
        if(row_prev != nullptr){
          row_prev->m_Next = row;
        }else{
          m->m_Rows = row;
        }
        break;

      }
      rows = rows->m_Next;
    }
  }
}

bool removeCell   ( TSPARSEMATRIX   * m,int rowIdx,int colIdx )
{
      //checking if the column exist
  TROWCOL *cols = m->m_Cols;

  TROWCOL *col_prev = nullptr;
  TROWCOL *col = nullptr; //the specific col box
  bool is_col = false;
  int num_col = 0;
  

  //loop through the columns
  while(cols != nullptr){
    if(cols->m_Idx == colIdx){
      col = cols;
      is_col = true;
      break;
    }
    num_col++;
    col_prev = cols;
    cols = cols->m_Next;
    
  }

  //checking if the row exist
  TROWCOL *rows = m->m_Rows;

  TROWCOL *row_prev = nullptr;
  TROWCOL *row = nullptr; //the specific row box
  bool is_row = false;
  int num_row = 0;

  //loop through row list
  while(rows != nullptr){
    if(rows->m_Idx == rowIdx){
      row = rows;
      is_row = true;
      break;
    }
    num_row++;
    row_prev = rows;
    rows = rows->m_Next;
  }

  //checking if both col and row exist
  if(is_row == false || is_col == false){
    return false;
  }

  //________REMOVING CELL FROM COL_______
  bool check_row_in_col = false;
  TCELL *cell_prev = nullptr;

  TCELL *cell = col->m_Cells;
  int count = 1;

  while(cell != nullptr){
    if(cell->m_Row == rowIdx){
      check_row_in_col = true;
      if(cell_prev != nullptr){
        cell_prev->m_Down = cell->m_Down;
      }else{
        col->m_Cells = nullptr;
      }
      //Changing the col boxes
      if(count == 1){
        if(cell->m_Down != nullptr){
          col->m_Cells = cell->m_Down;
        }else{
          if(col_prev != nullptr){
            col_prev->m_Next = col->m_Next;
          }
          if(num_col == 0){
            m->m_Cols = col->m_Next;
          }
          free(col);//NEED TO FREE THE COL BOX
        }
      }
      break;

    }
    count++;
    cell_prev = cell;
    cell = cell->m_Down;
  }

  if(check_row_in_col == false){
    return false;
  }

  //________REMOVING CELL FROM ROW__________
  bool check_col_in_row = false;
  TCELL *cell_prev2 = nullptr;

  TCELL *cell2 = row->m_Cells;
  int count2 = 1;

  while(cell2 != nullptr){
    if(cell2->m_Col == colIdx){
      check_col_in_row = true;
      if(cell_prev2 != nullptr){
        cell_prev2->m_Right = cell2->m_Right;
      }else{
        row->m_Cells = nullptr;
      }
      if(count2 == 1){
        if(cell2->m_Right != nullptr){
          row->m_Cells = cell2->m_Right;
        }else{
          if(row_prev != nullptr){
            row_prev->m_Next = row->m_Next;
          } 
          if(num_row == 0){
            m->m_Rows = row->m_Next;
          }
          free(row);//FREE THE ROW BOX
        }
      }
      free(cell2);
      break;

    }
    count2++;
    cell_prev2 = cell2;
    cell2 = cell2->m_Right;
    
  }

  if(check_col_in_row == false){
    return false;
  }

  return true;

}

void freeMatrix   ( TSPARSEMATRIX   * m )
{
    TROWCOL *col;
  TROWCOL *row;
  TCELL *cell;

  TROWCOL *cols = m->m_Cols;
  TROWCOL *rows = m->m_Rows;

  while(cols != nullptr){
    col = cols;

    cols = cols->m_Next;
    //COL
    TCELL *cell_tmp = col->m_Cells;
    while(cell_tmp != nullptr){
      cell = cell_tmp;

      cell_tmp = cell_tmp->m_Down;
      free(cell);
    }
    free(col);
  }
  

  while(rows != nullptr){
    row = rows;

    rows = rows->m_Next;

    free(row);
  }
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