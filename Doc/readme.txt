EKRAN PODGL¥DU:
<preview_screen.png>
<preview_screen2.png>

Podgl¹d widoku u¿ytkownika z kamery. Zielona i niebieska ramka to ramki kalibracyjne - u¿ytkownik musi trzymaæ praw¹ rêke tak, aby skóra jego d³oni wype³nia³a niebiesk¹ ramkê w ca³oœci. Na tej podstawie s¹ wyznaczane parametry pocz¹tkowe dla algorytmu camshift.

Lewa rêka u¿ytkownika musi znajdowaæ siê wewn¹trz zielonej ramki. Zaciœniêcie piêœci (lub usuniêcie rêki poza obszar ramki) a nastêpnie powrót do pozycji pocz¹tkowej rozpoznawane jest jako gest aktywacji.

Czerwona elipsa pokazuje po³o¿enie prawej rêki (wynik œledzenia algorytmu camshift).



EKRAN MENU:
<menu_screen.png>

Wizualizacja menu. U¿ytkownik ruchami r¹k mo¿e nawigowaæ po menu.



KONSOLA:
<console_screen.png>

W konsoli wyœwietlane s¹ pomocnicze informacje pozwalaj¹ce œledziæ przebieg programu. Wyœwietlane s¹ informacje o znalezionych gestach "GESTURE FOUND", numery gestów mo¿na porównaæ z nazwami sta³ych zdefiniowanych w pliku Gesture.hpp.

Dodatkowo pojawia siê informacja o sterowaniu maszyn¹ stanów menu ("Keeper: ...") oraz efekt wykonywania kodu podpiêtego pod akcje menu - w obecnej wersji wypisuj¹cego tylko na konsolê informacje o uruchamianej akcji ("Akcja: ...").


BACKPROJECTION:
<backprojection_screen.png>
<backprojection_screen2.png>
<backprojection_screen3.png>

Opis backprojection znajduje siê tutaj:
http://opencv.itseez.com/doc/tutorials/imgproc/histograms/back_projection/back_projection.html

Jest to wykorzystywane przez algorytm camshift (u nas œledzenie prawej rêki). Dodatkowo wyliczony backprojection u¿ywamy do wykrywania lewej rêki. Liczymy iloœæ dopasowanych punktów wewn¹trz zielonego prostok¹ta. Jeœli spadnie poni¿ej pewnego poziomu oznacza to, ¿e zmniejszy³o siê pole powierzchni rêki (np. zosta³a zaciœniêta w piêœæ). Zarówno œledzenie rêki jak i zaciskanie z punktu widzenia backprojection zosta³y pokazane na do³¹czonych obrazkach.