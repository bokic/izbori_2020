SELECT
	COALESCE(SUM(`izbiracko_mesto`.`ДПА`), 0) AS `ДПА`, 
	COALESCE(SUM(`izbiracko_mesto`.`ДЕМОКРАТИ`), 0) AS `ДЕМОКРАТИ`,
	COALESCE(SUM(`izbiracko_mesto`.`КОАЛИЦИЈА МОЖЕМЕ`), 0) AS `КОАЛИЦИЈА МОЖЕМЕ`,
	COALESCE(SUM(`izbiracko_mesto`.`ЛЕВИЦА`), 0) AS `ЛЕВИЦА`, 
	COALESCE(SUM(`izbiracko_mesto`.`АА / A`), 0) AS `АА / A`, 
	COALESCE(SUM(`izbiracko_mesto`.`ГЛАС ЗА МАКЕДОНИЈА`), 0) AS `ГЛАС ЗА МАКЕДОНИЈА`, 
	COALESCE(SUM(`izbiracko_mesto`.`ГДУ`), 0) AS `ГДУ`, 
	COALESCE(SUM(`izbiracko_mesto`.`ИНТЕГРА`), 0) AS `ИНТЕГРА`, 
	COALESCE(SUM(`izbiracko_mesto`.`ДУИ`), 0) AS `ДУИ`, 
	COALESCE(SUM(`izbiracko_mesto`.`СДУ`), 0) AS `СДУ`, 
	COALESCE(SUM(`izbiracko_mesto`.`ЕДИНСТВЕНА МАКЕДОНИЈА`), 0) AS `ЕДИНСТВЕНА МАКЕДОНИЈА`, 
	COALESCE(SUM(`izbiracko_mesto`.`МОРО`), 0) AS `МОРО`, 
	COALESCE(SUM(`izbiracko_mesto`.`ВМРО - ДПМНЕ и други`), 0) AS `ВМРО - ДПМНЕ и други`, 
	COALESCE(SUM(`izbiracko_mesto`.`ТВОЈА`), 0) AS `ТВОЈА`
FROM opstina
INNER JOIN izbiracko_mesto ON opstina.id = izbiracko_mesto.opstina_id