# Marine

Contents writer application for [track](https://tracks.run/).

This application allows you to create all types of content supported by Track.

## Installing / Getting started
### Prerequisites

- docker

## Setting up

> For windows users.
> 
> Take a look this [Marine on Windows](https://github.com/givery-technology/marine/wiki/Marine-on-Windows) document first, please.

### Start Marine

Run this command.

```
$ docker compose up -d
```

After the application started, you can access the app via `http://localhost:39000`

### Stop Marine

Run this command.

```
$ docker compose down
```
## Configuration

### Contents base directory

As default, Marine uses `./contents` as contents base directory. if you need to change the directory, pass `DBOOK_SRCDIR` via environment variable. See more details [here](https://github.com/givery-technology/marine/wiki/Configuration).

In the contents base directory, all of the contents that meet with conditions below will be picked up by Marine and displayed as the contents list. (**Recursively**)

- have `book.yml` or `track.yml`

See [Configuration](https://github.com/givery-technology/marine/wiki/Configuration) more advanced configuration. 

## Contents Creation Guide

You can see all of documents under the `./docs`. 

## Sample Contents

You can see all of sample contents under the `./contents`.


## Troubleshooting

See [Troubleshooting](https://github.com/givery-technology/marine/wiki/Troubleshooting) Guide.

## Licensing

Givery, inc. All Rights Reserved.

