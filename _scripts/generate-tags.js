const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");

function findVideoFilesRecursive(dir, arrayOfFiles) {
  const files = fs.readdirSync(dir);

  arrayOfFiles = arrayOfFiles || [];

  for (const file of files) {
    if (fs.statSync(`${dir}/${file}`).isDirectory()) {
      arrayOfFiles = findVideoFilesRecursive(`${dir}/${file}`, arrayOfFiles);
    } else {
      if (file !== 'index.md' && file.substring(file.length - 3, file.length) === '.md') {
        arrayOfFiles.push(path.join(dir, '/', file));
      }
    }
  }

  return arrayOfFiles;
}

function getVideoData() {
  const directories = [
    '_Tutoriales',
    '_Cursos',
    '_RetoProgramacion',
    '_Grabaciones'
  ];

  let files = [];
  for (const dir of directories) {
    findVideoFilesRecursive(dir, files);
  }

  const videos = [];

  for (const file of files) {
    const content = fs.readFileSync(`./${file}`, 'UTF8');
    const parsed = yaml.loadFront(content);
    videos.push({
      data: parsed,
    });
  }

  return videos;
}

function primeDirectory(dir) {

  fs.rmdirSync(dir, {
    recursive: true
  }, (err) => {
    if (err) {
      throw err;
    }
  });

  fs.mkdirSync(dir, err => {
    if (err) {
      throw err;
    }
  });

}


function writeTags(tag) {
  let description = `---
layout: tag
title: "#tags"
subtitle: "videos sobre #tags"
tag-name: tags
---`;
  description = description.replaceAll('tags', tag);

  fs.writeFileSync(`_tag/${tag}.md`, description);
}

function writeDescriptions(videos) {
  primeDirectory("./_tag");

  tags = []
  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;

    if (data.tags) {
      for (let i = 0; i < data.tags.length; ++i) {
        if (!tags.includes(data.tags[i])) {
          tags.push(data.tags[i]);
        }
      }
    }
  }

  for (let i = 0; i < tags.length; i++) {
    writeTags(tags[i])
  }
}

(() => {
  console.log("💫 Generador de Tags 💫");
  writeDescriptions(getVideoData());
})();
