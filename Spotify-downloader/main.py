import requests
import json
import base64
from apiclient.discovery import build
from pytube import YouTube
import ssl
import yt_dlp
import os

ssl._create_default_https_context = ssl._create_unverified_context
#change 
api_key = "secret"
CLIENT_ID = "secret"
CLIENT_SECRET = "secert"

youtube = build('youtube', 'v3', developerKey=api_key)


def get_url(title):
    request = youtube.search().list(q=title, part='snippet', type='video', maxResults=1)
    res = request.execute()
    for item in res['items']:
        title = item['snippet']['title']  # Video title
        video_id = item['id']['videoId']  # Video ID
        video_url = f"https://www.youtube.com/watch?v={video_id}"  # Construct URL
        return video_url


def download_youtube_video(url, save_path="."):
    ydl_opts = {
        "format": "mp4",
        "outtmpl": f"{save_path}/%(title)s.%(ext)s",
    }

    with yt_dlp.YoutubeDL(ydl_opts) as ydl:
        ydl.download([url])
    try:
        # Create YouTube object
        yt = YouTube(url)

        # Get the highest resolution stream
        stream = yt.streams.filter(file_extension="mp4", progressive=True).get_highest_resolution()

        # Print details of the video
        print(f"Title: {yt.title}")
        print(f"Downloading to: {save_path}")

        # Download the video
        stream.download(output_path=save_path)
        print("Download completed successfully!")
    except Exception as e:
        print(f"An error occurred: {e}")


def get_token():
    auth_string = CLIENT_ID + ":" + CLIENT_SECRET
    auth_bytes = auth_string.encode("utf-8")
    auth_base64 = str(base64.b64encode(auth_bytes), "utf-8")
    url = "https://accounts.spotify.com/api/token"

    headers = {
        "Authorization": "Basic " + auth_base64,
        "Content-Type": "application/x-www-form-urlencoded"
    }
    data = {"grant_type": "client_credentials"}
    result = requests.post(url, headers=headers, data=data)
    json_result = json.loads(result.content)
    token = json_result["access_token"]
    return token


def get_auth_token(token):
    return {"Authorization": "Bearer " + token}


def get_playlist(token, Id):
    url = "https://api.spotify.com/v1/users/" + Id + "/playlists"

    headers = get_auth_token(token)
    query = f"?q=id&type=playlist"
    query_url = url + query
    result = requests.get(query_url, headers=headers)
    json_result = json.loads(result.content)
    print("choose a playlist:")
    for i in range(len(json_result.get("items"))):
        print(i + 1, ".", json_result["items"][i]["name"])
    temp = input()
    num = int(temp)
    return json_result.get("items")[num - 1]["id"], json_result.get("items")[num - 1]["name"]


def extract_songs_from_playlist(token, playlist_id):
    url = "https://api.spotify.com/v1/playlists/" + playlist_id
    headers = get_auth_token(token)
    result = requests.get(url, headers=headers)
    json_result = json.loads(result.content)
    song_list = []

    # Extract playlist tracks
    tracks = json_result['tracks']['items']  # List of track objects

    for item in tracks:
        track = item['track']
        track_name = track.get('name')  # Get the song name
        artist_names = ', '.join(artist['name'] for artist in track.get('artists', []))  # Combine artist names
        song_list.append(f"{track_name} by {artist_names}")  # Add formatted string to the list

    return song_list


def connect_apis(track_list, dir_name):
    #change this
    path = "C:\\Users\\uriel\\Music\\" + dir_name

    # Create the directory
    try:
        os.mkdir(path)
        print(f"Directory '{dir_name}' created successfully.")
    except FileExistsError:
        print(f"Directory '{dir_name}' already exists.")
    except PermissionError:
        print(f"Permission denied: Unable to create '{dir_name}'.")
    except Exception as e:
        print(f"An error occurred: {e}")
    for item in track_list:
        download_youtube_video(get_url(item), path)


token = get_token()
#change user id
playlist_id, playlist_name = get_playlist(token, "user-id")

connect_apis(extract_songs_from_playlist(token, playlist_id), playlist_name)
