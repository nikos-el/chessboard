class ChessBoardArray {  
  protected:  
    class Row {  
      public:  
        Row(ChessBoardArray &a, int i): board(a), row(i) {}  
        int & operator [] (int i) const { return board.select(row,i); }  
  
      private:  
        ChessBoardArray &board;  
        int row;  
    };  
  
    class ConstRow {  
      public:  
        ConstRow(const ChessBoardArray &a, int i): board(a), row(i) {}  
        int operator [] (int i) const { return board.select(row,i); }  
  
      private:  
        const ChessBoardArray &board;  
        int row;  
    };  
  
  public:  
    ChessBoardArray(unsigned size = 0, unsigned x = 0): n(size), base(x), data(new int[(n*n+1)/2]) {  
      for (unsigned i=0; i<(n*n+1)/2; i++) data[i]=0;  
    }  
    ChessBoardArray(const ChessBoardArray &a): n(a.n), base(a.base), data(new int[(n*n+1)/2]) {  
      for (unsigned i=0; i<(n*n+1)/2; i++) data[i]=a.data[i];  
    }  
    ~ChessBoardArray() { delete [] data; }  
  
    ChessBoardArray & operator = (const ChessBoardArray &a){  
      delete [] data;  
      n=a.n; base=a.base;  
      data=new int[(n*n+1)/2];  
      for (unsigned i=0; i<(n*n+1)/2; i++) data[i]=a.data[i];  
      return *this;  
    }   
  
    int & select(int i, int j) { return data[loc(i,j)]; }  
    const int & select(int i, int j) const { return data[loc(i,j)]; }  
  
    const Row operator [] (int i) { return Row(*this, i); }  
    const ConstRow operator [] (int i) const { return ConstRow(*this, i); }  
  
    friend ostream & operator << (ostream &out, const ChessBoardArray &a){  
      for (unsigned i=0; i<a.n; i++){  
        for (unsigned j=0; j<a.n; j++){  
          if ((i+j)%2==0) out<<setw(4)<<a[i+a.base][j+a.base];  
          else out<<setw(4)<<0;  
        }  
        out<<endl;  
      }  
      return out;  
    }  
  
  private:  
    unsigned n, base;  
    int *data;  
  
    unsigned int loc(int i, int j) const throw(out_of_range){  
      int di=i-base, dj=j-base;  
      if (di<0 || dj<0 || di>=n || dj>=n || (di+dj)%2!=0) throw out_of_range("invalid index");   
      return ((di+1)/2)*((n+1)/2)+(di/2)*(n/2)+dj/2;  
    }  
};  
