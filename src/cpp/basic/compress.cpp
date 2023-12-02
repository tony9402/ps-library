sort($1.begin(), $1.end());
$1.erase(unique($1.begin(), $1.end()), $1.end());