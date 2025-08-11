void MainWindow::on_equal_clicked()
{
    std::string str = ui->line_edit->text().toStdString();
    QString chaine = "+,-,*,/,^";
    QStringList list;
    int pos = 0;
    std::vector<char> operate;
    std::vector<double> number;

    while (pos < str.size()) {
        std::string tmp;

        if (str[pos] == '-') {
            tmp.push_back(str[pos]);  // Ajouter le signe négatif au nombre
            ++pos;
        }

        // Lire le nombre
        while (pos < str.size() && !chaine.contains(str[pos])) {
            tmp.push_back(str[pos]);
            ++pos;
        }

        number.push_back(QString::fromStdString(tmp).toDouble());

        // Lire l'opérateur
        if (pos < str.size() && chaine.contains(str[pos])) {
            operate.push_back(str[pos]);
            ++pos;
        }
    }

    // Gérer les opérations avec priorité
    for (int i = 0; i < operate.size(); ++i) {
        if (operate[i] == '^') {
            number[i] = pow(number[i], number[i + 1]);
        }
    }

    for (int i = 0; i < operate.size(); ++i) {
        if (operate[i] == '*' || operate[i] == '/') {
            if (operate[i] == '*') {
                number[i] = number[i] * number[i + 1];
            } else {
                if (number[i + 1] != 0) {
                    number[i] = number[i] / number[i + 1];
                } else {
                    // Gérer la division par zéro
                    ui->line_edit->setText("Error: Division by zero");
                    return;
                }
            }

            // Supprimer le nombre suivant
            number.erase(number.begin() + i + 1);
            // Supprimer l'opérateur actuel
            operate.erase(operate.begin() + i);
            // Décrémenter i pour compenser la suppression
            --i;
        }
    }

    // Gérer les opérations avec priorité
    for (int i = 0; i < operate.size(); ++i) {
        if (operate[i] == '+' || operate[i] == '-') {
            if (operate[i] == '+') {
                number[i] = number[i] + number[i + 1];
            } else {
                number[i] = number[i] - number[i + 1];
            }
            // Supprimer le nombre suivant
            number.erase(number.begin() + i + 1);
            // Supprimer l'opérateur actuel
            operate.erase(operate.begin() + i);
            // Décrémenter i pour compenser la suppression
            --i;
        }
    }

    // Afficher le résultat
    QString result;
    result.setNum(number[0]);
    ui->line_edit->setText(ui->line_edit->text() + " = " + result);
}
