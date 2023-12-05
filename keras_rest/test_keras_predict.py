import chess
import numpy as np
import requests
import json

api_url = "http://localhost:10001/predict"

def make_matrix(board):
    pgn = board.epd()
    foo = []
    pieces = pgn.split(" ", 1)[0]
    rows = pieces.split("/")
    for row in rows:
        foo2 = []
        for thing in row:
            if thing.isdigit():
                for i in range(0, int(thing)):
                    foo2.append('.')
            else:
                foo2.append(thing)
        foo.append(foo2)
    return foo

def translate(matrix,chess_dict):
    rows = []
    for row in matrix:
        terms = []
        for term in row:
            terms.append(chess_dict[term])
        rows.append(terms)
    return rows

chess_dict = {
    'p' : [1,0,0,0,0,0,0,0,0,0,0,0],
    'P' : [0,0,0,0,0,0,1,0,0,0,0,0],
    'n' : [0,1,0,0,0,0,0,0,0,0,0,0],
    'N' : [0,0,0,0,0,0,0,1,0,0,0,0],
    'b' : [0,0,1,0,0,0,0,0,0,0,0,0],
    'B' : [0,0,0,0,0,0,0,0,1,0,0,0],
    'r' : [0,0,0,1,0,0,0,0,0,0,0,0],
    'R' : [0,0,0,0,0,0,0,0,0,1,0,0],
    'q' : [0,0,0,0,1,0,0,0,0,0,0,0],
    'Q' : [0,0,0,0,0,0,0,0,0,0,1,0],
    'k' : [0,0,0,0,0,1,0,0,0,0,0,0],
    'K' : [0,0,0,0,0,0,0,0,0,0,0,1],
    '.' : [0,0,0,0,0,0,0,0,0,0,0,0],
}

chess_board = chess.Board()

response = requests.post(api_url, "123")

matrix = make_matrix(chess_board)
board = translate(matrix,chess_dict)
board = np.array(board)
board = np.reshape(board,(1,8,8,12))
flattened_board = np.reshape(board, -1).tolist()
board_json = json.dumps(flattened_board)

pred = requests.post(api_url, data={"board":board_json}).json()
print(pred)

chess_board = chess.Board()
for i in range(100):
    matrix = make_matrix(chess_board)
    board = translate(matrix,chess_dict)
    board = np.array(board)
    board = np.reshape(board,(1,8,8,12))
    flattened_board = np.reshape(board, -1).tolist()
    board_json = json.dumps(flattened_board)

    response = requests.post(api_url, data={"board":board_json}).json()
    pred = response["output"]
    legal_moves = str(chess_board.legal_moves)[36:-2].replace(',','').split()
    index = int(round(len(legal_moves)*pred))
    chess_board.push_san(legal_moves[index])
    if chess_board.is_checkmate():
        break
chess_board