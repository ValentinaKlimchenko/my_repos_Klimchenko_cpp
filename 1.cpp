#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class Shape
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() = default;
};

class Triangle : public Shape
{
public:
    Triangle()
    {
        std::cout << "Enter the 1st side ";
        std::cin >> side_1;
        std::cout << std::endl;
        std::cout << "Enter the 2nd side ";
        std::cin >> side_2;
        std::cout << std::endl;
        std::cout << "Enter the 3rd side ";
        std::cin >> side_3;
        std::cout << std::endl;
    }
    double area() const override
    {
        double p = (side_1 + side_2 + side_3) / 2;
        return sqrt((p - side_1)*(p - side_2)*(p - side_3)*p);
    }
    double perimeter() const override
    {
        return side_1 + side_2 + side_3;
    }
private:
    double side_1;
    double side_2;
    double side_3;

};

class Circle : public Shape
{
public:
    Circle()
    {
        std::cout << "Enter the radius ";
        std::cin >> radius;
        std::cout << std::endl;
    }
    double area() const override
    {
        return 3.14*radius*radius;
    }
    double perimeter() const override
    {
        return 2*3.14*radius;
    }
private:
    double radius;
};

class  Rectangle : public Shape
{
public:
     Rectangle()
     {
        std::cout << "Enter the 1st side ";
        std::cin >> side_1;
        std::cout << std::endl;
        std::cout << "Enter the 2nd side ";
        std::cin >> side_2;
        std::cout << std::endl;
     }
     double area() const override
    {
        return side_1*side_2;
    }
    double perimeter() const override
    {
        return 2*(side_1 + side_2);
    }
protected:
    double side_1;
    double side_2;
};

class  Square : public Shape
{
public:
     Square()
     {
        std::cout << "Enter the side ";
        std::cin >> side;
        std::cout << std::endl;
     }
     double area() const override
    {
        return side*side;
    }
    double perimeter() const override
    {
        return 4*side;
    }
private:
    double side;
};

int main()
{
    std::cout << "Enter the number of shapes ";
    std::vector<double> s;
    std::vector<double> p;
    int n;
    std::cin >> n;
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Enter the shape type ";
        std::string name;

        std::cin >> name;
        if (name == "Triangle")
        {
            Triangle t;
            s.push_back(t.area());
            p.push_back(t.perimeter());

        }
        if (name == "Circle")
        {
            Circle t;
            s.push_back(t.area());
            p.push_back(t.perimeter());

        }
        if (name == "Rectangle")
        {
            Rectangle t;
            s.push_back(t.area());
            p.push_back(t.perimeter());
        }
        if (name == "Square")
        {
            Square t;
            s.push_back(t.area());
            p.push_back(t.perimeter());
        }
    }
    std::cout << "the squares of these figures ";
    for (int i = 0; i < n; i++)
    {
        std::cout << s[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "the perimeter of these figures ";
    for (int i = 0; i < n; i++)
    {
        std::cout << p[i] << " ";
    }

}
