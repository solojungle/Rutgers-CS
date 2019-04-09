PRIN INFO & DATA

# September 12, 2018

Introduction to SQL - Monotonic queries Three-liners

Why SQL?

- "what to do" rather than "how do it".
- avoid data-manipulation details
- database management system figures out optimal way, "query optimization"

Select-From-Where statements

(DEFINITION FROM SLIDES)

- Relation schema = relation name and attribute list.
  Optionally: types of attributes.
  Example: Beers(name, manf) or Beers(name: string, manf: string)
- Database = collection of relations.
- Database schema = set of all relation schemas in the database.

Meaning of Single-Relation Query

- Begin with relation in FROM clause
- horizontal cut = SELECT
- vertical cut = WHERE

Operational Semantics

- Data independence
- Go to car mechanic to get it fixed, come back with only 1 gear
- Programmer will not know there is an index

Complex Conditions in WHERE Clause

- AND, OR, NOT
- <>
- <
- \>
- <=
- \>=

Patterns

- Can be used a search function, fuzzy match

Multirelation Queries

- Interesting queries often combine data from more than one relation
- JOIN

Joining Two Relations

- Start with table that need FROM first
- Using JOIN will increase performance

Lots of papers on how to estimate the size of JOIN, (Relational Algebra)

Explicit Tuple-Variables

What does this query return?

```SQL
Select L1.drinker
From Likes L1, Likes L2
//SELF-JOIN
Where L1.drinker = L2.drinker AND L1.beer != L2.beer)
```

- A: Drinkers who do not like the same beer
- B: Drinkers who do not like any beer
- (C): Drinkers who like at least two beers
- D: Drinkers who like at most two beers

Student who do not take databases

- Whats wrong with this query is that, a student who takes multiple classes will not be excluded from the query

```
Ali | Math
Ali | Database // Will exclude this but keep everything else
Ali | Science
```

May be this one?

- t.student = t1.student
- t1 has to connected to t, else you would return all students

# September 14, 2018

## Tough v.s. easy queries

1. Nonmonotone (anti-monotone), can I add more and the query has less?
   - Monotonic queries are easy, more you add, more you get
   - Nonmonotone: give me all students who do not take Database, add new tuple that removes a student from the query (more you add, less you get).
   - "People who only frequent Joe's bar" + Adds new tuple that removes one of the results = Nonmonotone
   - Negation, Ceilings, Floors, Average, Equivalency
   - Tough queries indicated by words such as: "not", "only", "all", "at most", "whenever", "just"
   - Require subqueries and correlated variables

"You are in the circle of trust"

# September 19, 2018

Outer join

Aggregations (Favorite usage of SQL)

- groupby

Eliminate duplicates in an Aggregation:

```SQL
SELECT count (DISTINCT price)
FROM sells
WHERE beer = 'Bud';
```
