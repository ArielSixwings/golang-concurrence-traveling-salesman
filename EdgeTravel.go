package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
)

var graph [192][192]int
var open [192]bool
var origin int
var destiny int
var base int
var bestdist = 9999999999
var next [2]int
var total int
var realpath = 0
var sum = 0
var expectededge int

/**
 * @brief      Reads lines.
 *
 * @param      path  The path
 *
 * @return     { n strings that are the lines of the file }
 */
func ReadLines(path string) ([]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()
	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines, scanner.Err()
}

/**
 * @brief      { build the path by going to the next vertex using the edge weight as parameter }
 *
 * @param      initial       The initial
 * @param      expectededge  The expectededge
 *
 * @return     { the path, the total distance and a bool jey to change or not the best distance }
 */
func NextByMinimum(initial int, expectededge int) ([]int, int, bool) {
	var dist int
	var iteration = 0
	path := make([]int, 193)

	for i := initial; i < 192; i++ {
		next[0] = 33177600
		if i > 0 {
			next[1] = 0
		} else {
			next[1] = 1
		}
		for j := 0; j < 192; j++ {
			if j != i { //if origin is not he destiny
				if next[0] > graph[i][j] && open[j] && graph[i][j] > 0 { //if it is smaller,change
					next[0] = graph[i][j]
					next[1] = int(j)
				}
			}
		}
		total = total + next[0] //total dist is now bigger
		path[i] = next[1]       //the next spot

		iteration++

		/*------------------------PODA------------------------*/

		if (total + (192-iteration)*expectededge) > bestdist {
			return path, dist, false
		}
		open[next[1]] = false //next spot is now closed
	}

	for i := 0; i < initial; i++ {
		next[0] = 33177600
		if i > 0 {
			next[1] = 0
		} else {
			next[1] = 1
		}
		for j := 0; j < 192; j++ {
			if j != i { //if origin is not he destiny
				if next[0] > graph[i][j] && open[j] && graph[i][j] > 0 { //if it is smaller,change
					next[0] = graph[i][j]
					next[1] = int(j)
				}
			}
		}
		total = total + next[0] //total dist is now bigger
		path[i] = next[1]       //the next spot

		iteration++

		/*------------------------PODA------------------------*/

		if (total + (192-iteration)*expectededge) > bestdist {
			return path, dist, false
		}
		open[next[1]] = false //next spot is now closed
	}
	for i := 0; i < 193; i++ {
	}
	return path, dist, true
}

func main() {
	var dist int
	var change bool
	var newdist int
	path := make([][]int, 192)
	for i := 0; i < 192; i++ {
		path[i] = make([]int, 193)
	}

	distances := make([]int, 192)
	total = 0

	_, err := fmt.Scanf("%d", &base)
	//path[0] = base - 1
	//path[192] = base - 1
	for i := 0; i < (2 * (192 * 191)); i++ {
		_, err = fmt.Scanf("%d", &origin)
		_, err = fmt.Scanf("%d", &destiny)
		_, err = fmt.Scanf("%d", &dist)
		if err != nil {
			fmt.Println("here man")
			return
		}
		graph[(origin - 1)][(destiny - 1)] = dist
	}
	for i := 0; i < 192; i++ {
		sum = sum + distances[i]
	}
	for i := 0; i < 192; i++ {
		open[i] = true
		graph[i][i] = 0

	}
	for i := 0; i < 192; i++ {
		for j := 0; j < 192; j++ {
			distances[j] = graph[i][j]
		}
		sort.Ints(distances)
		for k := 0; k < 8; k++ {
			sum = sum + distances[k]
		}
	}
	expectededge = int(sum / 192 * 8)

	for i := 0; i < 192; i++ {
		fmt.Println("Building path: ", i)
		path[i], newdist, change = NextByMinimum(i, expectededge)
		if change {
			fmt.Println("path changed")
			bestdist = newdist
			realpath = i
		} else {
			fmt.Println("path isn't good")
		}

	}
	for i := 0; i < 191; i++ {

	}
	lines, err := ReadLines("internalspots.txt")
	if err != nil {
		log.Fatalf("readLines: %s", err)
	}
	fmt.Println(0)
	fmt.Println(0)
	fmt.Println(0)
	fmt.Println(1)
	for i := 0; i < 193; i++ {
		fmt.Println(path[realpath][i] + 1)
	}

	for i := 0; i < len(lines); i++ {
		fmt.Println(lines[i])
	}

}
