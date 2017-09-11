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
