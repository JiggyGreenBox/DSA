# Queries
### 1. not equal, with null values
```sql
Input: 
Customer table:
+----+------+------------+
| id | name | referee_id |
+----+------+------------+
| 1  | Will | null       |
| 2  | Jane | null       |
| 3  | Alex | 2          |
| 4  | Bill | null       |
| 5  | Zack | 1          |
| 6  | Mark | 2          |
+----+------+------------+
Output: 
+------+
| name |
+------+
| Will |
| Jane |
| Bill |
| Zack |
+------+

select name from Customer where referee_id != 2 OR referee_id IS NULL;
/*
In most programming languages, a condition is either True or False. 
In SQL, there is a third option: Unknown.

When you compare a value to NULL using standard operators like = or !=, 
the result is not True or False — it is Unknown

SQL is only returning true values, excluding false and unknown


*/
SELECT name 
FROM Customer 
WHERE COALESCE(referee_id, 0) != 2;
-- "Look at referee_id. If it's NULL, treat it as a 0 instead."
```

### 2. not equal to null
In SQL, **nothing** is equal to `NULL`, not even `NULL` itself
```sql
--You might be tempted to write:
WHERE referee_id != NULL. 
--In SQL, nothing is equal to NULL, not even NULL itself.
```

**use the specific keywords** `IS NULL` or `IS NOT NULL`

### 3. The "Aggregate Rule"
As a rule of thumb for interviews: If you have an aggregate function (like COUNT, SUM, AVG, MIN, MAX) in your SELECT alongside a normal column, that normal column MUST appear in the GROUP BY clause.
```sql
-- If you run 
SELECT customer_id, COUNT(visit_id),
--  the database tries to do this:

customer_id: Wants to show three separate values (54, 54, 30).

COUNT(visit_id): Wants to show one single value (3).

The database can't display a table that is 3 rows tall in one column and only 1 row tall in the next. It’s like trying to put a giant box into a tiny drawer.
```