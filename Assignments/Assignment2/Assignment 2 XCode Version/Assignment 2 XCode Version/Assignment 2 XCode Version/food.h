#pragma once
#include <string>

class Food {
private:
    std::string m_name;
    float m_calories;

public:
    Food(std::string name, float calories) : m_name{ name }, m_calories{ calories } {}

    std::string name() const { return m_name; }

    float calories() const { return m_calories; }

    Food operator+(const Food& rhs) const;

    bool operator<(const Food& rhs) const;

    bool operator==(const Food& rhs) const;

};

    std::ostream& operator<<(std::ostream& os, const Food& rhs);

