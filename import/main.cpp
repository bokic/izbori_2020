#include <QSqlDatabase>
#include <QTextStream>
#include <QTextCodec>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage <input.cvs> <output.db>\n");

        return EXIT_FAILURE;
    }

    QFile cvs(argv[1]);

    cvs.open(QIODevice::ReadOnly | QIODevice::Text);

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(argv[2]);

    if (!db.open())
    {
        printf("Error creating database file.\nError: %s\n", db.lastError().text().toUtf8().constData());

        return EXIT_FAILURE;
    }

    db.exec("BEGIN TRANSACTION");
    db.exec("CREATE TABLE opstina('id' INTEGER PRIMARY KEY, 'izborna_edinica' INTEGER NOT NULL, 'ime' TEXT NOT NULL)");
    db.exec("CREATE TABLE izbiracko_mesto('id' INTEGER PRIMARY KEY, 'opstina_id' INTEGER NOT NULL, 'broj' TEXT NOT NULL, 'ДПА' INTEGER, 'ДЕМОКРАТИ' INTEGER, 'КОАЛИЦИЈА МОЖЕМЕ' INTEGER, 'ЛЕВИЦА' INTEGER, 'АА / A' INTEGER, 'ГЛАС ЗА МАКЕДОНИЈА' INTEGER, 'ГДУ' INTEGER, 'ИНТЕГРА' INTEGER, 'ДУИ' INTEGER, 'СДУ' INTEGER, 'ЕДИНСТВЕНА МАКЕДОНИЈА' INTEGER, 'МОРО' INTEGER, 'ВМРО - ДПМНЕ и други' INTEGER, 'ТВОЈА' INTEGER)");

    QSqlQuery select_opstina_id("SELECT id FROM opstina WHERE izborna_edinica = ? AND ime = ?");
    QSqlQuery insert_opstina("INSERT INTO opstina(izborna_edinica, ime) VALUES(?, ?)");

    QSqlQuery select_izbiracko_mesto("SELECT opstina_id FROM izbiracko_mesto WHERE broj = ?");
    QSqlQuery insert_izbiracko_mesto("INSERT INTO izbiracko_mesto(broj, opstina_id) VALUES(?, ?)");

    QTextStream in(&cvs);
    in.setCodec(QTextCodec::codecForName("UTF-8"));

    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList items = line.split(',');

        if(items.count() != 5)
            continue;

        int opstina_id;

        auto izborna_edinica = items[0].trimmed();
        auto opstina = items[1].trimmed();
        auto izbiracko_mesto = items[2].trimmed();
        auto partija = items[3].trimmed();
        auto glasovi = items[4].trimmed();

        select_opstina_id.bindValue(0, izborna_edinica);
        select_opstina_id.bindValue(1, opstina);
        select_opstina_id.exec();

        if (!select_opstina_id.next())
        {
            insert_opstina.bindValue(0, izborna_edinica);
            insert_opstina.bindValue(1, opstina);
            insert_opstina.exec();
            opstina_id = insert_opstina.lastInsertId().toInt();
        }
        else
        {
            opstina_id = select_opstina_id.value(0).toInt();
        }

        select_izbiracko_mesto.bindValue(0, izbiracko_mesto);
        select_izbiracko_mesto.exec();

        if (!select_izbiracko_mesto.next())
        {
            insert_izbiracko_mesto.bindValue(0, izbiracko_mesto);
            insert_izbiracko_mesto.bindValue(1, opstina_id);
            insert_izbiracko_mesto.exec();
        }

        db.exec(QString("UPDATE izbiracko_mesto SET `%1` = %2 WHERE broj = '%3'").arg(partija, glasovi, izbiracko_mesto));
    }

    db.exec("END TRANSACTION");

    return EXIT_SUCCESS;
}
