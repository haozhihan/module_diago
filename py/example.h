// example.h
#ifndef EXAMPLE_H
#define EXAMPLE_H

class Example
{
  public:
    Example(int value) : value(value)
    {
    }
    int getValue() const
    {
        return value;
    }
    void setValue(int newValue)
    {
        value = newValue;
    }

  private:
    int value;
};

#endif // EXAMPLE_H
