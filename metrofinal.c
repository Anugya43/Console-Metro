#include <stdio.h>
#include <limits.h>
#include <string.h>
#define V 11
#define FARE_PER_KM 2.0
// Structure to represent a station
typedef struct {
	char name[50];
	char placesToVisit[100];
}station;
//struct Station stations[V];
 station stations[V];
 void initializeStations(){
  
	strcpy(stations[0].name, "Shaheed Sthal");
    strcpy(stations[0].placesToVisit, "Hanuman temple, Drizzling Water park");
    strcpy(stations[1].name, "Shyam Park");
    strcpy(stations[1].placesToVisit, "Opulent mall, IP Cinema");
    strcpy(stations[2].name, "Hindon");
    strcpy(stations[2].placesToVisit, "Gurudwara, Fruit Market");
    strcpy(stations[3].name, "Major Mohan Nagar");
    strcpy(stations[3].placesToVisit, "Park, RDC Mall");
    strcpy(stations[4].name, "Majlis Park");
    strcpy(stations[4].placesToVisit, "Majlis Park, Ganga Cinema");
    strcpy(stations[5].name, "Dilshad Garden");
    strcpy(stations[5].placesToVisit, "Shopping Mall, Dilshad Garden");
    strcpy(stations[6].name, "Jhilmil");
    strcpy(stations[6].placesToVisit, "Turab Market, JHV Cinema");
    strcpy(stations[7].name, "Welcome");
    strcpy(stations[7].placesToVisit, "Reliance Shopping Mall, Blue Line metro");
	strcpy(stations[8].name, "Kashmere gate");
    strcpy(stations[8].placesToVisit, "Yellow line, Cannaought Place");
    strcpy(stations[9].name, "Rithala");
    strcpy(stations[9].placesToVisit, "End gate");
}
// Function to find the station with the minimum distance value
int minDistance(int distance[], int shortestPathSet[]) {
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++) {
		if (!shortestPathSet[v] && distance[v] <= min) {
			min = distance[v];
			min_index = v;
		}
	}

	return min_index;
}


// Dijkstra's algorithm to find the shortest path between two stations
void dijkstra(int graph[V][V], int src, int dest) {
	int distance[V];     // The output array distance[i] holds the shortest distance from src to i
	int shortestPathSet[V]; // shortestPathSet[i] is true if station i is included in the shortest path tree or the shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and shortestPathSet[] as false
	for (int i = 0; i < V; i++) {
		distance[i] = INT_MAX;
		shortestPathSet[i] = 0;
	}

	// Distance from source station to itself is always 0
	distance[src] = 0;

	// Find the shortest path for all stations
	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(distance, shortestPathSet);
		shortestPathSet[u] = 1;

		// Update distance value of the adjacent stations
		for (int v = 0; v < V-1; v++) {
			if (!shortestPathSet[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
				distance[v] = distance[u] + graph[u][v];
			}
		}
	}

	

	// Print the shortest distance between the source and destination stations
	printf("\nShortest Distance from station %s to station %s is: %d\n", stations[src].name, stations[dest].name, distance[dest]);
	 calculateFare(distance[dest]);
};

// Function to calculate and print the fare based on the distance
void calculateFare(int distance) {
    double fare =  FARE_PER_KM * distance;

    printf("\nFare for the journey: Rs %.2f\n", fare);
	};

void displayPlacesToVisit(int stationIndex) {
    printf("\nPlaces to visit near %s: %s\n", stations[stationIndex].name, stations[stationIndex].placesToVisit);
}

	int graph[V][V] = {
		{0, 2, 4, 0, 0, 0, 0, 0, 0, 0},
		{2, 0, 1, 7, 0, 0, 0, 0, 0, 0},
		{4, 1, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 7, 3, 0, 5, 2, 0, 0, 0, 0},
		{0, 0, 0, 5, 0, 0, 6, 0, 0, 0},
		{0, 0, 0, 2, 0, 0, 1, 8, 0, 0},
		{0, 0, 0, 0, 6, 1, 0, 9, 3, 0},
		{0, 0, 0, 0, 0, 8, 9, 0, 4, 2},
		{0, 0, 0, 0, 0, 0, 3, 4, 0, 6},
		{0, 0, 0, 0, 0, 0, 0, 2, 6, 0}
	};
	void displayStationNames() {
		printf("List of Metro Stations:\n");
		for (int i = 0; i <V-1; i++) {
			printf("%d. %s\n", i, stations[i].name);
		}
	}

int main() {
	int source, destination;
	initializeStations();
    displayStationNames();
    
	printf("\nEnter source station (0-9): ");
	scanf("%d", &source);

	printf("\nEnter destination station (0-9): ");
	scanf("%d", &destination);

	if (source < 0 || source >= V || destination < 0 || destination >= V) {
		printf("Invalid input. Stations should be between 0 and 09.\n");
		return 1;
	}
	dijkstra(graph, source, destination);
	displayPlacesToVisit(destination);
	return 0;                 
}