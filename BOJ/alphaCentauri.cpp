#include<iostream>
#include<math.h>

using namespace std;

int main(void)
{
	int testCase,j=0;
	int startingPlanet, targetPlanet, distance, maxSquere = 1, stair,extra;
	int output[1000];

	cin >> testCase;

	//output = (int*)malloc(sizeof(int)*testCase);
	
	while (testCase--)
	{
		cin >> startingPlanet >> targetPlanet;
		distance = targetPlanet - startingPlanet;
		
		while (maxSquere++)
		{
			if (maxSquere >= sqrt(distance))
			{
				maxSquere = (maxSquere - 1);
				break;
			}
		}

		if (maxSquere == 1)
			stair = 1;
		else
			stair = 2 * (maxSquere) - 1;
		extra = distance - maxSquere*maxSquere;
		
		if (extra == 0)
			output[j++] = stair;
		else if (extra <= maxSquere && extra != 0)
			output[j++] = stair + 1;
		else
			output[j++] = stair + 2;

		maxSquere = 1;
	}
	
	testCase = 0;
	
	while (j--)
		cout << output[testCase++] << endl;
	
	return 0;
}