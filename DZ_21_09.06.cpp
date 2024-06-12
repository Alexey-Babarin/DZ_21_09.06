#include <iostream>
#include <vector>
#include <fstream>

// Абстрактный базовый класс Shape
class Shape 
{
public:
    // Виртуальный деструктор
    virtual ~Shape() {}

    // Чисто виртуальные методы, которые должны быть определены в производных классах
    virtual void Show() const = 0; // Вывод информации о фигуре
    virtual void Save(std::ofstream& out) const = 0; // Сохранение фигуры в файл
    virtual void Load(std::ifstream& in) = 0; // Считывание фигуры из файла
};

// Класс Square, производный от Shape
class Square : public Shape 
{
    int x, y; // Координаты левого верхнего угла
    int side; // Длина стороны
public:
    Square(int x, int y, int side) : x(x), y(y), side(side) {} // Конструктор

    void Show() const override 
    {
        std::cout << "Square at (" << x << ", " << y << ") with side " << side << std::endl;
    }

    void Save(std::ofstream& out) const override 
    {
        out << "Square " << x << " " << y << " " << side << std::endl;
    }

    void Load(std::ifstream& in) override 
    {
        in >> x >> y >> side;
    }
};

// Класс Rectangle, производный от Shape
class Rectangle : public Shape 
{
    int centerX, centerY; // Координаты центра
    int width, height; // Ширина и высота
public:
    Rectangle(int centerX, int centerY, int width, int height)
        : centerX(centerX), centerY(centerY), width(width), height(height) {} // Конструктор

    void Show() const override 
    {
        std::cout << "Rectangle with center at (" << centerX << ", " << centerY << ") and dimensions " << width << "x" << height << std::endl;
    }

    void Save(std::ofstream& out) const override 
    {
        out << "Rectangle " << centerX << " " << centerY << " " << width << " " << height << std::endl;
    }

    void Load(std::ifstream& in) override 
    {
        in >> centerX >> centerY >> width >> height;
    }
};

// Класс Ellipse, производный от Shape
class Ellipse : public Shape 
{
    int upperLeftX, upperLeftY; // Координаты верхнего левого угла
    int width, height; // Ширина и высота
public:
    Ellipse(int upperLeftX, int upperLeftY, int width, int height)
        : upperLeftX(upperLeftX), upperLeftY(upperLeftY), width(width), height(height) {} // Конструктор

    void Show() const override 
    {
        std::cout << "Ellipse with upper left corner at (" << upperLeftX << ", " << upperLeftY << ") and dimensions " << width << "x" << height << std::endl;
    }

    void Save(std::ofstream& out) const override 
    {
        out << "Ellipse " << upperLeftX << " " << upperLeftY << " " << width << " " << height << std::endl;
    }

    void Load(std::ifstream& in) override 
    {
        in >> upperLeftX >> upperLeftY >> width >> height;
    }
};

// Функция для сохранения массива фигур в файл
void SaveShapes(const std::vector<Shape*>& shapes, const std::string& filename) 
{
    std::ofstream out(filename);
    for (const auto& shape : shapes) 
    {
        shape->Save(out);
    }
}

// Функция для загрузки массива фигур из файла
void LoadShapes(std::vector<Shape*>& shapes, const std::string& filename) 
{
    std::ifstream in(filename);
    std::string shapeType;
    while (in >> shapeType) {
        if (shapeType == "Square") 
        {
            int x, y, side;
            in >> x >> y >> side;
            shapes.push_back(new Square(x, y, side));
        }
        else if (shapeType == "Rectangle") 
        {
            int centerX, centerY, width, height;
            in >> centerX >> centerY >> width >> height;
            shapes.push_back(new Rectangle(centerX, centerY, width, height));
        }
        else if (shapeType == "Ellipse") 
        {
            int upperLeftX, upperLeftY, width, height;
            in >> upperLeftX >> upperLeftY >> width >> height;
            shapes.push_back(new Ellipse(upperLeftX, upperLeftY, width, height));
        }
    }
}

// Главная функция
int main() 
{
    // Создание массива фигур
    std::vector<Shape*> shapes;
    shapes.push_back(new Square(10, 10, 100));
    shapes.push_back(new Rectangle(50, 50, 80, 60));
    shapes.push_back(new Ellipse(70, 70, 120, 80));

    // Сохранение фигур в файл
    SaveShapes(shapes, "shapes.txt");

    // Очистка массива фигур
    for (auto& shape : shapes) 
    {
        delete shape;
    }
    shapes.clear();

    // Загрузка фигур из файла в другой массив
    std::vector<Shape*> loadedShapes;
    LoadShapes(loadedShapes, "shapes.txt");

    // Вывод информации о каждой фигуре
    for (const auto& shape : loadedShapes) 
    {
        shape->Show();
    }

    // Очистка загруженного массива фигур
    for (auto& shape : loadedShapes) 
    {
        delete shape;
    }

    return 0;
}