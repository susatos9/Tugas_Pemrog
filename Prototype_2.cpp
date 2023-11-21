#include <bits/stdc++.h>
using namespace std;


struct dataku
{
    int x; int y;
    int arr1[100][100] = {0};

    void initialize(int a, int b){
        x = a;
        y = b;
    }

    void fillarray(){
        cout << "Input array : " << endl;
        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++){
                cin >> arr1[i][j];
            }
        }
    }

    void printarray(){
        if (x == 0 || y == 0)
        {
            cout << "Array is empty" << endl;
            return;
        }
        
        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++){
                cout << arr1[i][j] << " ";
            }
            cout << endl;
        }
    }

    void tambah(dataku p){
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                arr1[i][j] += p.arr1[i][j];
            }
            
        }
    }

    void row_echelon() {
        for (int i = 0; i < y; ++i) { 
            // Find the pivot element in the current column
            int pivotRow = i;
            while (pivotRow < y && arr1[pivotRow][i] == 0) {
                ++pivotRow;
            }

            if (pivotRow == y) {
                // Skip if the entire column is zero
                continue;
            }

            // Swap the current row with the row containing the pivot element
            for (int j = 0; j < x; ++j) {
                std::swap(arr1[i][j], arr1[pivotRow][j]);
            }

            // Scale the pivot row to make the pivot element 1
            double pivotElement = arr1[i][i];
            for (int j = i; j < x; ++j) {
                arr1[i][j] /= pivotElement;
            }

            // Eliminate non-zero elements below the pivot
            for (int k = i + 1; k < y; ++k) {
                double factor = arr1[k][i];
                for (int j = i; j < x; ++j) {
                    arr1[k][j] -= factor * arr1[i][j];
                }
            }
        }
    }

    double square_determinant() {
        if (x != y)
        {
            cout << "Not a funtion for non sqare determinant" << endl;
            return 0.0;
        }
        double det = 1;
            for (int i = 0; i < x; i++) {
            // Pivoting
            int max_row = i;
            for (int j = i + 1; j < x; j++) {
                if (abs(arr1[j][i]) > abs(arr1[max_row][i])) {
                    max_row = j;
                }
            }
            if (max_row != i) {
                // Swap rows if needed
                for (int k = 0; k < x; k++) {
                    swap(arr1[i][k], arr1[max_row][k]);
                }
                // Changing the sign because of row swap
                det = -det;
            }
            // Making the matrix upper triangular
            for (int j = i + 1; j < x; j++) {
                double ratio = arr1[j][i] / arr1[i][i];
                for (int k = i; k < x; k++) {
                    arr1[j][k] -= ratio * arr1[i][k];
                }
            }
            det *= arr1[i][i];
            // Jika elemen diagonal utama menjadi nol, determinan adalah 0
            if (arr1[i][i] == 0) {
                return 0;
            }
        }

        return det;
    }
    
         
};

int determinant(dataku a){
    a.row_echelon();
    int minimal = min(a.x, a.y);
    int hasil = 0;
    for (int i = 0; i < minimal; i++)
    {
        hasil += a.arr1[i][i];
    }
    return hasil;
    
}


dataku multiply_matrix(dataku a, dataku b){
    int column_a = a.x;
    int row_a = a.y;
    int column_b = b.x;
    int row_b = b.y;
    dataku hasil;

    if (row_a != column_b)
    {
        cout << "ERROR matrix cannot multiplied" << endl;
        return hasil;
    }
    
    
    hasil.initialize(row_a, column_b);

    for (int i = 0; i < row_a; i++)
    {
        for (int j = 0; j < column_b; j++)
        {
            for (int k = 0; k < column_a; k++)
            {
                hasil.arr1[i][j] += a.arr1[i][k] * b.arr1[k][j];
            }
            
        }
    }
    return hasil;   
}


double determinan(dataku x){
    x.row_echelon();
    int batas = min(x.x, x.y);
    double hasil;
    for (int i = 0; i < batas; i++)
    {
        hasil += x.arr1[i][i];
    }
    return hasil;
    
}


void simpleUI(dataku x, dataku y){
    int pilihan;
    int exit = 0;
    while (exit == 0){
        cout << "Pilih salah satu operasi dibawah untuk dilakukan" << endl;
        cout << "1 : Input kedua matriks;         2 : penjumlahan kedua matriks" << endl;
        cout << "3 : perkalian kedua matriks;     4 : mencetak kedua matriks" << endl;
        cout << "5 : row echelon operation for both matrix; 6: determinan kedua matriks" << endl;
        cout << "0 : exit " << endl;
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            int x1, y1,x2,y2;
            cout << "column and row for each of matrix one and two : "; cin >> x1 >> y1 >> x2 >> y2;
            x.initialize(x1,y1); x.fillarray();
            y.initialize(x2,y2); y.fillarray();
            break;
        case 2:
            x.tambah(y);
            break;
        case 3:
            x =multiply_matrix(x,y);
            break;
        case 4:
            x.printarray(); cout << endl;
            y.printarray(); cout << endl;
            break;
        case 5:
            x.row_echelon(); y.row_echelon();
            break;
        case 6:
            double hasil1, hasil2;
            if (x.x == x.y)
            {
                hasil1 =  x.square_determinant();
            }
            else{
                hasil1 = determinan(x);
            }
            if (y.x == y.y)
            {
                hasil2 =  x.square_determinant();
            }
            else{
                hasil2 = determinan(x);
            }
            cout << "Determinan matriks 1 adalah : " << hasil1 << " Dan determinan matriks 2 adalah : " << endl;
            
        case 0:
            exit = 1;
            break;
        default:
            break;
        }
    }
}


int main(){
    dataku tes1, tes2;
    simpleUI(tes1,tes2);

    return 0;
}

