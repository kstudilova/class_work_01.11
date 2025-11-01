#include <iostream>

void destroy(int ** mtx, size_t created) 
{
    for (size_t i = 0; i < created; i++)
    {
        delete[] mtx[i];
    }
    delete[] mtx;
}

int ** create(size_t rows, size_t cols)
{
    int ** mtx  = new int * [rows];
    size_t created = 0;
    try 
    {
        for (; created < rows; ++created) //(size_t i = 0; i < rows; ++i)
        {
            mtx[created]  = new int[cols]; //new может сгенерировать исключение 
        }
    }
    catch (const std::bad_alloc & e)
    {
        destroy(mtx, created);
        throw; //опрокинится в вызывающую функцию main
    }
    return mtx;
}

void construct(int ** mtx, int init, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            mtx[i][j] = init;
        }
    }
}

void input(int ** mtx, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            std::cin >> mtx[i][j];
        }
    }
}

void output(int ** mtx, const size_t * lns, size_t rows)
{
    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << ' ' << mtx[i][0];
        for (size_t j = 1; j < lns[i]; ++j)
        {
            std::cout << " " << mtx[i][j];
        }
        std::cout <<  "\n";
    }

}

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows)
{
    int ** matrix = new int * [rows];
    size_t created = 0;
    size_t next_lns = 0;
    try
    {
        for (size_t i = 0; i < rows; ++i)
        {
            matrix[i] = new int[lns[i]];
            for (size_t j = 0; j < lns[i]; ++j)
            {
                matrix[i][j] = t[next_lns + j];
            }
            next_lns += lns[i];
            ++created;
        }
    } 
    catch (...) 
    {
        for (size_t i = 0; i < created; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        throw;
    }
    return matrix;
}

int main()
{
    size_t r = 0, c = 0;
    std::cin >> r >> c; //возвращает булевую переменнную, которая принимает значение false при некорректном вводе
    if (!std::cin) //если не гуд
    {
        std::cerr << "Incorrect input\n";
        return 2;
    }
    
    int ** matrix = nullptr;
    try
    {
        matrix = create(r, c);
    }
    catch(const std::bad_alloc & e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    std::cout << "created!\n";
    construct(matrix, 0, r, c);
    //std::cout << matrix[0][0] << "\n"; //UB?
    input(matrix, r, c);
    if (!std::cin)
    {
        destroy(matrix, r);
        std::cerr << "Input error\n";
        return 1;
    }
    output(matrix, r, c);

    destroy(matrix, r);

    int one_dim_array[] = {5,5,5,5,6,6,7,7,7,7,8};
    size_t n = 11;
    size_t lns[] = {4,2,4,1};
    size_t rows = 4;
    try {
        int** mat = convert(one_dim_array, n, lns, rows);
        output(mat, lns, rows);
        destroy(mat, rows);     
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        delete[] one_dim_array;
        delete[] lns;
        return 3;
    }

    delete[] one_dim_array;
    delete[] lns;
}