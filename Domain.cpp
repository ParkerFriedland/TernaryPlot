#include "Domain.h"

Domain::Domain(unsigned candidates) : _domain(std::vector<bool>(candidates)) 
{
	IncludeAll();
}

Domain::Domain(std::vector<bool> &domain) : _domain(domain) {}

void Domain::Include(unsigned candidate)
{
	_domain[candidate] = true;
}

void Domain::Exclude(unsigned candidate)
{
	_domain[candidate] = false;
}

void Domain::IncludeAll()
{
	for (bool candidate : _domain)
		candidate = true;
}

void Domain::ExcludeAll()
{
	for (bool candidate : _domain)
		candidate = false;
}

void Domain::SetDomain(std::vector<bool> &domain)
{
	_domain = domain;
}

std::vector<bool> &Domain::GetDomain()
{
	return _domain;
}

unsigned Domain::GetNumInDomain()
{
	unsigned num = 0;
	for (bool candidate : _domain)
		if (candidate)
			++num;
	return num;
}

unsigned Domain::GetNumCandidates()
{
	return _domain.size();
}

bool Domain::NextInDomain(unsigned &candidate)
{
	do
	{
		if (++candidate >= _domain.size())
			return false;
	} while (!_domain[candidate]);

	return true;
}