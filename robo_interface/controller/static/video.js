// const video = document.getElementById("video");
// const stream = new MediaSource();
// video.src = URL.createObjectURL(stream);
// stream.addEventListener("sourceopen", () => {
//   const sourceBuffer = stream.addSourceBuffer('video/webm; codecs="vp8"');
//   fetch("/stream_video/")
//     .then(response => response.arrayBuffer())
//     .then(arrayBuffer => sourceBuffer.appendBuffer(arrayBuffer))
//     .then(() => {
//       video.play();
//     });
// });
