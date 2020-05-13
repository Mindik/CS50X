SELECT title FROM movies, ratings WHERE movies.id IN (SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Chadwick Boseman"))
AND movies.id = ratings.movie_id ORDER BY rating DESC LIMIT 5;