# Marine

Book writer application for [CODEPREP](https://codeprep.jp/)

## Prerequisite

- docker
- docker-compose

## Start and Stop

```
docker-compose up -d
```

After the application started, you can access the app via `http://localhost:39000`

```
docker-compose down
```

## Using with a local Orca Server

Start your orca server with a particular port:

```
PORT=5000 ./orca
```

After Orca has started, run this command in your book's directory to start Marine:

```
docker run -e "ORCA_HOST=localhost:5000" -p 9000:9000 --rm -it -v $(pwd):/opt/docker/contents codeprep/marine
```

## How to update docker image
If any change comes with the docker image itself, you need to remove it once for upgrading it.

```
docker rmi codeprep/marine:newest
```

## How to use
Following directory names are listed in dropdown on header.

- under the `contents` directory
- which has `book.yml` file

Choose 1 of them.

## About contents directory
This directory is shared with docker container.

The book compiler will read source code of a book from this directory.

Checkout your book repository in this directory.

BookWriter is built as a docker image.
