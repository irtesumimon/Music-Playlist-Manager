#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for storing song information
typedef struct Song {
    char title[50];
    char album[50];
    int year;
    float duration;
    struct Song* next;
} Song;

// Structure for playlist
typedef struct Playlist {
    char name[50];
    Song* head;
    struct Playlist* next;
} Playlist;

Song* songList = NULL;
Playlist* playlistList = NULL;

// Function declarations
void createNewSong();
void displayAllSongs();
void createNewPlaylist();
void addSongToPlaylist();
void showPlaylist();
void playPreviousTrack();
void playNextTrack();
void exitPlayer();
void saveSongsToFile();
void loadSongsFromFile();
void savePlaylistsToFile();
void loadPlaylistsFromFile();
void displayMenu();
void delay(int seconds);

int main() {
    int choice, loggedIn = 0;
    char username[50], password[50];

    printf("----------------------------------------------------------------------\n");
    printf("                   Welcome to the Music Playlist App                  \n");
    printf("----------------------------------------------------------------------\n");
    printf("1. Sign In\n2. Sign Up\n3. Logout\n");
    printf("----------------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sign in process
            printf("----------------------------------------------------------------------\n");
            printf("                             Sign In                                  \n");
            printf("----------------------------------------------------------------------\n");
            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter Password: ");
            scanf("%s", password);
            loggedIn = 1;  // Assuming successful login
            printf("----------------------------------------------------------------------\n");
            printf("                         Logged in successfully!                      \n");
            printf("----------------------------------------------------------------------\n");
            break;
        case 2:
            // Sign up process
            printf("----------------------------------------------------------------------\n");
            printf("                             Sign Up                                  \n");
            printf("----------------------------------------------------------------------\n");
            printf("Create Username: ");
            scanf("%s", username);
            printf("Create Password: ");
            scanf("%s", password);
            printf("----------------------------------------------------------------------\n");
            printf("                       Creating your account...                       \n");
            printf("----------------------------------------------------------------------\n");
            delay(2);  // Add a delay of 2 seconds
            printf("----------------------------------------------------------------------\n");
            printf("                      Account created successfully!                   \n");
            printf("----------------------------------------------------------------------\n");
            loggedIn = 1;
            break;
        case 3:
            printf("----------------------------------------------------------------------\n");
            printf("                             Logging out...                           \n");
            printf("----------------------------------------------------------------------\n");
            return 0;
    }

    // If user successfully logged in
    if (loggedIn) {
        loadSongsFromFile();
        loadPlaylistsFromFile();
        while (1) {
            displayMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    createNewSong();
                    break;
                case 2:
                    displayAllSongs();
                    break;
                case 3:
                    createNewPlaylist();
                    break;
                case 4:
                    addSongToPlaylist();
                    break;
                case 5:
                    showPlaylist();
                    break;
                case 6:
                    playPreviousTrack();
                    break;
                case 7:
                    playNextTrack();
                    break;
                case -1:
                    exitPlayer();
                    break;
                default:
                    printf("Invalid choice, try again.\n");
                    break;
            }
        }
    }
    return 0;
}

void createNewSong() {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (!newSong) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("                         Create a New Song                            \n");
    printf("----------------------------------------------------------------------\n");
    printf("Enter title: ");
    scanf(" %[^\n]%*c", newSong->title);
    printf("Enter album name: ");
    scanf(" %[^\n]%*c", newSong->album);
    printf("Enter year of release: ");
    scanf("%d", &newSong->year);
    printf("Enter duration (in minutes): ");
    scanf("%f", &newSong->duration);

    newSong->next = NULL;

    if (songList == NULL) {
        songList = newSong;
    } else {
        Song* temp = songList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }

    saveSongsToFile();

    char choice;
    printf("----------------------------------------------------------------------\n");
    printf("Do you want to create another song? (y/n): ");
    scanf(" %c", &choice);
    printf("----------------------------------------------------------------------\n");
    if (choice == 'y' || choice == 'Y') {
        createNewSong();
    }
}

void displayAllSongs() {
    Song* temp = songList;
    if (temp == NULL) {
        printf("----------------------------------------------------------------------\n");
        printf("                     No songs available.                              \n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("                         Available Songs                              \n");
    printf("----------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("Title: %s, Album: %s, Year: %d, Duration: %.2f\n",
               temp->title, temp->album, temp->year, temp->duration);
        temp = temp->next;
    }
    printf("----------------------------------------------------------------------\n");
}

void createNewPlaylist() {
    Playlist* newPlaylist = (Playlist*)malloc(sizeof(Playlist));
    if (!newPlaylist) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("                        Create a New Playlist                         \n");
    printf("----------------------------------------------------------------------\n");
    printf("Enter playlist name: ");
    scanf(" %[^\n]%*c", newPlaylist->name);
    newPlaylist->head = NULL;
    newPlaylist->next = NULL;

    if (playlistList == NULL) {
        playlistList = newPlaylist;
    } else {
        Playlist* temp = playlistList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPlaylist;
    }

    savePlaylistsToFile();
    printf("----------------------------------------------------------------------\n");
    printf("Playlist '%s' created successfully.\n", newPlaylist->name);
    printf("----------------------------------------------------------------------\n");
}

void addSongToPlaylist() {
    if (playlistList == NULL) {
        printf("----------------------------------------------------------------------\n");
        printf("                     No playlists available.                          \n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    char playlistName[50];
    displayAllSongs(); // Show all songs
    printf("----------------------------------------------------------------------\n");
    printf("Enter the playlist name to which you want to add a song: ");
    scanf(" %[^\n]%*c", playlistName);

    Playlist* playlist = playlistList;
    while (playlist != NULL && strcmp(playlist->name, playlistName) != 0) {
        playlist = playlist->next;
    }

    if (playlist == NULL) {
        printf("----------------------------------------------------------------------\n");
        printf("                     Playlist not found.                             \n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    char songTitle[50];
    printf("Enter the song title to add: ");
    scanf(" %[^\n]%*c", songTitle);

    Song* song = songList;
    while (song != NULL && strcmp(song->title, songTitle) != 0) {
        song = song->next;
    }

    if (song == NULL) {
        printf("----------------------------------------------------------------------\n");
        printf("                     Song not found.                                 \n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    // Add song to the playlist
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (!newSong) {
        printf("Memory allocation failed!\n");
        return;
    }
    *newSong = *song; // Copy song data
    newSong->next = playlist->head;
    playlist->head = newSong;

    savePlaylistsToFile();
    printf("----------------------------------------------------------------------\n");
    printf("Song '%s' added to playlist '%s' successfully.\n", song->title, playlist->name);
    printf("----------------------------------------------------------------------\n");
}

void showPlaylist() {
    if (playlistList == NULL) {
        printf("----------------------------------------------------------------------\n");
        printf("                     No playlists available.                          \n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    char playlistName[50];
    printf("----------------------------------------------------------------------\n");
    printf("Enter playlist name to show: ");
    scanf(" %[^\n]%*c", playlistName);

    Playlist* playlist = playlistList;
    while (playlist != NULL && strcmp(playlist->name, playlistName) != 0) {
        playlist = playlist->next;
    }

    if (playlist == NULL) {
        printf("----------------------------------------------------------------------\n");
        printf("                     Playlist not found.                             \n");
        printf("----------------------------------------------------------------------\n");
        return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("Songs in Playlist '%s':\n", playlist->name);
    Song* temp = playlist->head;
    if (temp == NULL) {
        printf("No songs in this playlist.\n");
    } else {
        while (temp != NULL) {
            printf("Title: %s, Album: %s, Year: %d, Duration: %.2f\n",
                   temp->title, temp->album, temp->year, temp->duration);
            temp = temp->next;
        }
    }
    printf("----------------------------------------------------------------------\n");
}

void playPreviousTrack() {
    // Placeholder for functionality to play the previous track
    printf("----------------------------------------------------------------------\n");
    printf("Functionality for playing the previous track not implemented yet.\n");
    printf("----------------------------------------------------------------------\n");
}

void playNextTrack() {
    // Placeholder for functionality to play the next track
    printf("----------------------------------------------------------------------\n");
    printf("Functionality for playing the next track not implemented yet.\n");
    printf("----------------------------------------------------------------------\n");
}

void exitPlayer() {
    printf("----------------------------------------------------------------------\n");
    printf("                         Exiting music player...                      \n");
    printf("----------------------------------------------------------------------\n");
    saveSongsToFile();
    savePlaylistsToFile();
    exit(0);
}

void saveSongsToFile() {
    FILE* file = fopen("songs.txt", "w");
    if (file == NULL) {
        printf("Failed to open songs file for writing.\n");
        return;
    }

    Song* temp = songList;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%d,%.2f\n", temp->title, temp->album, temp->year, temp->duration);
        temp = temp->next;
    }
    fclose(file);
}

void loadSongsFromFile() {
    FILE* file = fopen("songs.txt", "r");
    if (file == NULL) return;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        Song* newSong = (Song*)malloc(sizeof(Song));
        if (!newSong) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        sscanf(line, "%[^,],%[^,],%d,%f", newSong->title, newSong->album, &newSong->year, &newSong->duration);
        newSong->next = songList;
        songList = newSong;
    }
    fclose(file);
}

void savePlaylistsToFile() {
    FILE* file = fopen("playlists.txt", "w");
    if (file == NULL) {
        printf("Failed to open playlists file for writing.\n");
        return;
    }

    Playlist* temp = playlistList;
    while (temp != NULL) {
        fprintf(file, "%s\n", temp->name);
        Song* songTemp = temp->head;
        while (songTemp != NULL) {
            fprintf(file, "  %s,%s,%d,%.2f\n", songTemp->title, songTemp->album, songTemp->year, songTemp->duration);
            songTemp = songTemp->next;
        }
        temp = temp->next;
    }
    fclose(file);
}

void loadPlaylistsFromFile() {
    FILE* file = fopen("playlists.txt", "r");
    if (file == NULL) return;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        Playlist* newPlaylist = (Playlist*)malloc(sizeof(Playlist));
        if (!newPlaylist) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        sscanf(line, "%[^\n]", newPlaylist->name);
        newPlaylist->head = NULL;
        newPlaylist->next = NULL;

        while (fgets(line, sizeof(line), file) && line[0] == ' ') {
            Song* newSong = (Song*)malloc(sizeof(Song));
            if (!newSong) {
                printf("Memory allocation failed!\n");
                fclose(file);
                return;
            }
            sscanf(line + 2, "%[^,],%[^,],%d,%f", newSong->title, newSong->album, &newSong->year, &newSong->duration);
            newSong->next = newPlaylist->head;
            newPlaylist->head = newSong;
        }

        if (playlistList == NULL) {
            playlistList = newPlaylist;
        } else {
            Playlist* temp = playlistList;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newPlaylist;
        }
    }
    fclose(file);
}

void displayMenu() {
    printf("----------------------------------------------------------------------\n");
    printf("                            Music Player Menu                         \n");
    printf("----------------------------------------------------------------------\n");
    printf("1. Create a new song\n");
    printf("2. Display all available songs\n");
    printf("3. Create a new playlist\n");
    printf("4. Add a song to the playlist\n");
    printf("5. Show playlist\n");
    printf("6. Play previous track\n");
    printf("7. Play next track\n");
    printf("-1. Exit music player\n");
    printf("----------------------------------------------------------------------\n");
}

void delay(int seconds) {
    int milliSeconds = 1000 * seconds;
    clock_t startTime = clock();
    while (clock() < startTime + milliSeconds);
}
