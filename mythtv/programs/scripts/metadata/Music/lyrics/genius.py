# -*- Mode: python; coding: utf-8; indent-tabs-mode: nil; -*-

from common import culrcwrap
from lib.culrcscrapers.genius.lyricsScraper import LyricsFetcher
# make sure this-------^^^^^^^^^ matches this file's basename

info = {
    'name':        'Genius',
    'description': 'Search http://www.genius.com for lyrics',
    'author':      'Paul Harrison and ronie',
    'priority':    '200',
    'syncronized': False,
    'artist':      'Maren Morris',
    'title':       'My Church',
}

if __name__ == '__main__':
    culrcwrap.main(__file__, info, LyricsFetcher)
