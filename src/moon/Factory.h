#ifndef MOON_FACTORY_H
#define MOON_FACTORY_H

#include <vector>
#include <map>

namespace moon {
	
	template<class Tbase>
	class CreatorBase {
	public:
		virtual ~CreatorBase() {}
		virtual Tbase * create() const = 0;
	};
	
	template<class Product, class Tbase>
	class Creator : public CreatorBase<Tbase> {
	public:
		virtual Tbase * create() const 
		{ 
			Product* obj = new Product;
			return static_cast<Tbase*>(obj);
		}
	};
	
	template<typename Tid, class Tbase>
	class Factory {
	public:
		bool registerObject(Tid type, CreatorBase<Tbase> * pCreator);
		void unregisterObject(Tid type);
		Tbase * create(Tid type);
		typedef std::vector<Tid> IdentifierList;
		IdentifierList getIdentifierList();
	private:
		typedef std::map<Tid, CreatorBase<Tbase> *> CreatorMap;
		CreatorMap creatormap;
	};
	
	template<typename Tid, class Tbase>
	bool Factory<Tid, Tbase>::registerObject(Tid type, CreatorBase<Tbase> * pCreator)
	{
		typename CreatorMap::iterator it = creatormap.find(type);
		if (it != creatormap.end()) {
			delete pCreator;
			return false;
		}
		creatormap[type] = pCreator;
		return true;
	}
	
	template<typename Tid, class Tbase>
	void Factory<Tid, Tbase>::unregisterObject(Tid type)
	{
		typename CreatorMap::iterator it = creatormap.find(type);
		if (it == creatormap.end()) 
			return;
		delete it->second;
		creatormap.erase(it);
	}
	
	template<typename Tid, class Tbase>
	Tbase * Factory<Tid, Tbase>::create(Tid type)
	{
		typename CreatorMap::iterator it = creatormap.find(type);
		if (it == creatormap.end()) 
			return NULL;
		
		CreatorBase<Tbase> * pCreator = (*it).second;
		return pCreator->create();
	}
	
	template<typename Tid, class Tbase>
	std::vector<Tid> Factory<Tid, Tbase>::getIdentifierList()
	{
		std::vector<Tid> vec;
		for (typename CreatorMap::iterator i = creatormap.begin(); i != creatormap.end(); i++)
			vec.push_back(i->first);
		return vec;
	}
	
} // namespace

#endif
