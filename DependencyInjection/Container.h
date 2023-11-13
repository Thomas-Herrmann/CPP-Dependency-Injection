#include<memory>
#include<functional>
#include<type_traits>

namespace injection
{
	static class Registrar
	{
		friend class Container;

	private:
		class Registration
		{

		};

		template<class TInterface, class TImplementation>
		class WithClause
		{
		public:
			template<class... TDependencies>
			std::unique_ptr<Registration> With(std::shared_ptr<std::function<std::shared_ptr<TImplementation>(std::shared_ptr<TDependencies>...)>> constructor)
			{
				return std::make_unique<Registration>();
			}
		};

		template<class TInterface>
		class ImplementationClause
		{
		public:
			template<class TImplementation>
			std::unique_ptr<WithClause<TInterface, TImplementation>> To()
			{
				static_assert(std::is_base_of<TInterface, TImplementation>::value, "Cannot bind class to non-descendant class");

				return std::make_unique<WithClause<TInterface, TImplementation>>();
			}
		};

		template<class TInterface>
		friend std::unique_ptr<ImplementationClause<TInterface>> Bind();
	};

	template<class TInterface>
	static std::unique_ptr<Registrar::ImplementationClause<TInterface>> Bind()
	{
		return std::make_unique<Registrar::ImplementationClause<TInterface>>();
	}

	class Container 
	{
	public:
		void Register(std::unique_ptr<Registrar::Registration> registration)
		{

		}

		template<class TInterface>
		std::shared_ptr<TInterface> Resolve()
		{

		}
	};
}