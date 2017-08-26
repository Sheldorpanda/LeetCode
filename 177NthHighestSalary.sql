CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  DECLARE M INT;
  SET M = N - 1;
  RETURN (
      # Write your MySQL query statement below.
      SELECT * FROM (
            SELECT DISTINCT Salary FROM Employee
            ORDER BY Salary DESC
      ) AS T
      LIMIT 1 OFFSET M
  );
END