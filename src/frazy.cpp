#include "Phrases.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

std::vector<std::string> generatePhrases() {
    std::vector<std::string> phrases = {
            "szybki brązowy lis", "jaskółka okrążyła dom", "pięć plus pięć to dziesięć",
            "C++ jest mocny", "programowanie jest zabawą", "trzymaj się kodu",
            "algorytmy i struktury danych", "klawiatura to potęga", "kompilator i debugowanie",
            "kodu nie można złamać", "wszystko zaczyna się od pomysłu", "czysty kod to dobry kod",
            "zmienne i stałe", "pętle i warunki", "operacje na tablicach", "programowanie obiektowe",
            "dziedziczenie i polimorfizm", "klasy i obiekty", "interfejsy i implementacje",
            "testowanie jednostkowe", "zarządzanie pamięcią", "programowanie wielowątkowe",
            "biblioteki standardowe", "nazwa zmiennej mówi wszystko", "komentarze są kluczowe",
            "wersjonowanie kodu", "debugowanie krok po kroku", "integracja ciągła",
            "refaktoryzacja kodu", "wzorce projektowe", "kontrola wersji", "systemy operacyjne",
            "bazy danych i SQL", "struktury danych", "złożoność obliczeniowa", "algorytmy sortowania",
            "algorytmy wyszukiwania", "grafy i drzewa", "rekurencja", "paradygmaty programowania",
            "programowanie funkcyjne", "programowanie reaktywne", "debugowanie z użyciem gdb",
            "profilowanie kodu", "optymalizacja wydajności", "programowanie mobilne",
            "programowanie webowe", "backend i frontend", "API i mikroserwisy",
            "konteneryzacja i Docker", "chmura obliczeniowa", "serverless computing",
            "sztuczna inteligencja", "uczenie maszynowe", "sieci neuronowe", "analiza danych",
            "przetwarzanie równoległe", "programowanie GPU", "bezpieczeństwo aplikacji",
            "szyfrowanie i kryptografia", "uwierzytelnianie i autoryzacja", "ochrona przed atakami",
            "pola bitowe", "zliczanie bitów", "programowanie systemowe", "kompilacja i linkowanie",
            "narzędzia deweloperskie", "IDE i edytory kodu", "kontrola błędów",
            "architektura oprogramowania", "modelowanie danych", "standardy kodowania",
            "automatyzacja zadań", "programowanie w Pythonie", "programowanie w Javie",
            "programowanie w C#", "programowanie w JavaScripcie", "TypeScript i Angular",
            "React i Redux", "Node.js i Express", "Spring Boot i Hibernate",
            "Ruby on Rails", "Django i Flask", "Symfony i Laravel", "programowanie w Rust",
            "programowanie w Go", "programowanie w Swift", "programowanie w Kotlinie",
            "Tworzenie gier w Unity", "Unreal Engine", "Tworzenie aplikacji mobilnych",
            "Flutter i Dart", "React Native", "sztuczna inteligencja i gry",
            "symulacje i modelowanie", "automatyzacja testów", "Selenium i TestNG",
            "Jest i Mocha", "testowanie integracyjne", "testowanie wydajnościowe",
            "monitorowanie aplikacji", "logowanie i analityka", "DevOps i CI/CD",
            "Ansible i Terraform", "Kubernetes i Helm", "administracja systemami",
            "zarządzanie konfiguracją", "skrypty powłoki", "Bash i PowerShell",
            "edytory tekstu", "Vim i Emacs", "edytory graficzne", "GIMP i Photoshop",
            "tworzenie grafiki wektorowej", "Inkscape i Illustrator", "modelowanie 3D",
            "Blender i Maya", "tworzenie animacji", "renderowanie i kompozycja",
            "postprodukcja wideo", "Adobe Premiere i After Effects", "muzyka komputerowa",
            "FL Studio i Ableton", "programowanie dźwięku", "sztuka cyfrowa",
            "projektowanie UX/UI", "prototypowanie i testowanie", "Wireframing",
            "tworzenie stron internetowych", "HTML i CSS", "JavaScript i jQuery",
            "frameworki CSS", "Bootstrap i Bulma", "projektowanie responsywne",
            "tworzenie interfejsów użytkownika", "zastosowania technologii AR/VR",
            "realność wirtualna i rozszerzona", "projektowanie gier komputerowych",
            "mechanika i fizyka gier", "programowanie AI w grach", "sztuczna inteligencja",
            "systemy rekomendacyjne", "sieci neuronowe i uczenie głębokie", "analityka danych",
            "Big Data i Hadoop", "Spark i Kafka", "Internet Rzeczy", "IoT i Edge Computing",
            "Smart Home i automatyka", "programowanie systemów wbudowanych", "Arduino i Raspberry Pi",
            "robotyka i automatyka", "sterowanie i regulacja", "programowanie PLC",
            "cyberbezpieczeństwo", "ochrona danych osobowych", "prawo IT", "audyt i certyfikacja",
            "metodyki zwinne", "Scrum i Kanban", "zarządzanie projektami IT", "Prince2 i PMP",
            "analiza biznesowa", "modelowanie procesów biznesowych", "automatyzacja marketingu",
            "SEO i SEM", "zarządzanie treścią", "WordPress i Joomla", "e-commerce",
            "platformy sprzedażowe", "projektowanie doświadczeń użytkownika", "badania użyteczności",
            "analiza rynku i konkurencji", "strategia produktowa", "rozwój produktu",
            "cykl życia oprogramowania", "tworzenie dokumentacji technicznej", "przywództwo w IT",
            "budowanie zespołu", "motywacja i zarządzanie zespołem", "rozwój kariery w IT",
            "sieci komputerowe", "TCP/IP i routing", "zarządzanie serwerami", "Linux i Windows Server",
            "systemy plików", "backup i odtwarzanie", "chmura prywatna i hybrydowa", "AWS i Azure",
            "Google Cloud Platform", "DevSecOps", "bezpieczeństwo sieci", "firewalle i IDS/IPS",
            "zarządzanie ryzykiem", "strategia bezpieczeństwa", "certyfikaty bezpieczeństwa",
            "programowanie sterowników", "interfejsy sprzętowe", "debugowanie sprzętu",
            "projektowanie PCB", "symulacje obwodów", "komunikacja szeregowa",
            "Bluetooth i Wi-Fi", "ZigBee i Z-Wave", "LoRa i Sigfox", "komunikacja M2M",
            "przetwarzanie sygnałów", "obrazowanie cyfrowe", "analiza obrazów",
            "biometria i rozpoznawanie twarzy", "rozpoznawanie mowy", "sztuczna inteligencja i NLP",
            "przetwarzanie języka naturalnego", "machine learning i AI", "deep learning i TensorFlow",
            "Keras i PyTorch", "analiza danych i Pandas", "big data i Spark", "analiza biznesowa i Excel"
    };
    return phrases;
}

void savePhrasesToFile(const std::vector<std::string>& phrases, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& phrase : phrases) {
            file << phrase << std::endl;
        }
        file.close();
        std::cout << "Phrases saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

std::string getRandomPhrase(const std::vector<std::string>& phrases) {
    std::srand(static_cast<unsigned>(std::time(0))); // Initialize random seed
    int randomIndex = std::rand() % phrases.size(); // Generate random index
    return phrases[randomIndex];
}
