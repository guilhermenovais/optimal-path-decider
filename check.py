import os
import subprocess


class bcolors:
    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    ENDC = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"


def parse_graph(input_file):
    """Parses the input graph file and returns an adjacency dictionary."""
    with open(input_file, "r") as f:
        lines = f.read().splitlines()

    _, num_edges = map(int, lines[0].split())
    edges = {}

    for line in lines[1 : num_edges + 1]:
        u, v, w = line.rsplit(" ", 2)
        w = int(w)
        if u not in edges:
            edges[u] = {}
        if v not in edges:
            edges[v] = {}
        edges[u][v] = w
        edges[v][u] = w

    return edges


def calculate_path_cost(path, edges):
    """Calculates the total cost of the given path based on the adjacency dictionary."""
    cost = 0
    for i in range(len(path) - 1):
        u, v = path[i], path[i + 1]
        if v not in edges.get(u, {}):
            return None
        cost += edges[u][v]
    cost += edges[path[-1]][path[0]]
    return cost


def run_test_cases(executable, testcases_dir):
    input_dir = os.path.join(testcases_dir, "inputs")
    output_dir = os.path.join(testcases_dir, "outputs")

    for i in range(1, 11):
        print("")

        input_file = os.path.join(input_dir, f"testCase{i:02}.txt")
        expected_output_file = os.path.join(output_dir, f"testCase{i:02}.txt")

        if not os.path.exists(input_file) or not os.path.exists(expected_output_file):
            print(
                f"{bcolors.WARNING}Input or output file for testCase{i:02} is missing.{bcolors.ENDC}"
            )
            continue

        # Run the executable
        try:
            result = subprocess.run(
                [executable],
                input=open(input_file, "r").read(),
                text=True,
                capture_output=True,
                check=True,
            )
        except subprocess.CalledProcessError as e:
            print(f"{bcolors.FAIL}Error running testCase{i:02}: {e}{bcolors.ENDC}")
            continue

        # Get the expected and actual output
        actual_output = result.stdout.splitlines()
        with open(expected_output_file, "r") as f:
            expected_output = f.read().splitlines()

        if not actual_output:
            print(
                f"{bcolors.FAIL}Test case testCase{i:02} failed: No output produced.{bcolors.ENDC}"
            )
            continue

        expected_cost = int(expected_output[0])
        actual_cost = int(actual_output[0]) if actual_output[0].isdigit() else None
        errors = []

        # Check if the reported cost is incorrect
        if actual_cost is None or actual_cost != expected_cost:
            errors.append(
                f"{bcolors.FAIL}Incorrect cost. Expected: {expected_cost}, Got: {actual_output[0]}{bcolors.ENDC}"
            )

        # Parse graph and validate path cost
        edges = parse_graph(input_file)
        actual_path = actual_output[1].split()
        computed_cost = calculate_path_cost(actual_path, edges)

        # Check if the computed path cost matches the reported cost
        if computed_cost is None or computed_cost != actual_cost:
            errors.append(
                f"{bcolors.FAIL}Path does not match the given cost. Expected cost: {expected_cost}, Computed cost from path: {computed_cost}{bcolors.ENDC}"
            )

        # Print errors if any
        if errors:
            print(f"{bcolors.FAIL}Test case testCase{i:02} failed:{bcolors.ENDC}")
            for error in errors:
                print(error)
        else:
            print(f"{bcolors.OKGREEN}Test case testCase{i:02} passed!{bcolors.ENDC}")


if __name__ == "__main__":
    executable_path = "./tp3"
    testcases_path = "./testcases"

    if not os.path.exists(executable_path):
        print(f"{bcolors.FAIL}Executable not found.{bcolors.ENDC}")
    elif not os.path.exists(testcases_path):
        print(f"{bcolors.FAIL}Test cases directory not found.{bcolors.ENDC}")
    else:
        run_test_cases(executable_path, testcases_path)
