import os
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin

BASE_URL = "https://www.pgnmentor.com/files.html"
DEST_ROOT = "pgn"

def download_pgn_files():
    response = requests.get(BASE_URL)
    response.raise_for_status()

    soup = BeautifulSoup(response.text, "html.parser")

    links = [a['href'] for a in soup.find_all('a', href=True) if a['href'].lower().endswith('.zip') or a['href'].lower().endswith('.pgn')]

    print(f"Found {len(links)} PGN ZIP files.")

    for link in links:
        file_url = urljoin(BASE_URL, link)
        local_path = os.path.join(DEST_ROOT, link.replace("/", os.sep))

        os.makedirs(os.path.dirname(local_path), exist_ok=True)

        print(f"Downloading {local_path}...")
        r = requests.get(file_url)
        r.raise_for_status()
        with open(local_path, 'wb') as f:
            f.write(r.content)

    print("All PGN ZIP files downloaded!")

if __name__ == "__main__":
    download_pgn_files()
