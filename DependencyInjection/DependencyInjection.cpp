#include <iostream>
#include "Container.h"
#include <string>
#include <memory>
#include <functional>

class ITires
{
    virtual std::string GetBrandName() = 0;
};

class CompanyTires : ITires
{
    std::string GetBrandName()
    {
        return "Company";
    }
};

class ICar
{
    virtual std::string GetName() = 0;
};

class Rx7 : ICar
{
private:
    std::shared_ptr<ITires> _tires;

public:
    Rx7(std::shared_ptr<ITires> tires)
    {
        _tires = tires;
    }

    std::string GetName()
    {
        return "Rx7";
    }
};

std::shared_ptr<CompanyTires> CompanyTiresConstructor()
{
    return std::make_shared<CompanyTires>();
}

std::shared_ptr<Rx7> Rx7Constructor(std::shared_ptr<ITires> tires)
{
    return std::make_shared<Rx7>(tires);
}

int main()
{
    injection::Container container;

    container.Register(injection::Bind<ITires>()->To<CompanyTires>()->With<>(std::make_shared<std::function<std::shared_ptr<CompanyTires>()>>(&CompanyTiresConstructor)));
    container.Register(injection::Bind<ICar>()->To<Rx7>()->With<ITires>(std::make_shared<std::function<std::shared_ptr<Rx7>(std::shared_ptr<ITires>)>>(&Rx7Constructor)));
}