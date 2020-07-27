#include <vector>

#pragma once

class Domain
{
public:
	Domain(unsigned candidates);
	Domain(std::vector<bool> &domain);

	bool operator[](unsigned candidate) const;

	void Include(unsigned candidate);
	void Exclude(unsigned candidate);
	void IncludeAll();
	void ExcludeAll();

	void SetDomain(std::vector<bool> &domain);
	std::vector<bool> &GetDomain();
	unsigned GetNumInDomain();
	unsigned GetNumCandidates();

	bool NextInDomain(unsigned &candidate);

private:
	std::vector<bool> _domain;
};